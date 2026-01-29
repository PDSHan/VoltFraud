import paramiko
import time
import sys
from datetime import datetime, timedelta
import threading
import pyvisa as visa

REMOTE_HOST = "10.42.0.198"
USERNAME = "xxx"
PASSWORD = "123456"
MUL_PROCESS = "glitch_controll"
SGX_PROCESS = "app"
MEMORY_ACCESS = "memory_test"
HEALTH_CHECK_CMD = "echo ok"
CHECK_INTERVAL = 10


DCPower_ADDRESS = 'TCPIP::10.42.0.83::INSTR'
DCPower_resourceManager = None
DC_session = None
DC_channel4 = "3"
DC_channel1 = "1"
DC_channel2 = "2"
Unexpected_death = False

ssh = None
DCpower = None

def ssh_connect():
    global ssh
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(REMOTE_HOST, username=USERNAME, password=PASSWORD, timeout=5)
        print("SSH 连接成功")
    except Exception as e:
        print(f"SSH 连接失败: {e}")
        ssh = None

def ssh_disconnect():
    global ssh
    if ssh == None:
        pass
    else:
        ssh.close()

def is_host_alive():
    global ssh
    if ssh is None:
        ssh_connect()
        if ssh is None:
            return False
    result_container = {}
    def run_cmd():
        try:
            stdin, stdout, stderr = ssh.exec_command(HEALTH_CHECK_CMD)
            # 第二重保险：轮询 exit_status_ready 防止 read 卡死
            deadline = time.time() + 5  # 5秒超时
            output = []
            while time.time() < deadline:
                if stdout.channel.exit_status_ready():
                    output = stdout.read().decode().strip()
                    break
                time.sleep(0.1)
            else:
                raise TimeoutError("stdout.read() 超时")
            result_container["out"] = output
        except Exception as e:
            result_container["error"] = str(e)

    # 第一重保险：防止 exec_command 卡住
    t = threading.Thread(target=run_cmd)
    t.start()
    t.join(timeout=6)  # 给 run_cmd 最多 6 秒时间

    if t.is_alive():
        print("健康检查失败: exec_command 卡死，强制断开 SSH")
        # ssh.close()
        ssh = None
        return False
    if "error" in result_container:
        print(f"健康检查失败: {result_container['error']}")
        ssh = None
        return False
    if result_container.get("out") == "ok":
        # print("健康检查成功")
        return True
    else:
        ssh = None
        print(f"健康检查失败: 输出={result_container.get('out')}")
        return False


restart = True
def is_process_running(program_name):
    global ssh, restart, Unexpected_death
    result_container = {}
    if restart:
        return "not_running"

    def run_cmd():
        try:
            stdin, stdout, stderr = ssh.exec_command(f"pgrep -x {program_name}")
            # 防止 stdout.read() 卡住，轮询 exit_status_ready
            deadline = time.time() + 5
            output = None
            while time.time() < deadline:
                if stdout.channel.exit_status_ready():
                    output = stdout.read().decode().strip()
                    break
                time.sleep(0.1)
            else:
                raise TimeoutError("stdout.read() 超时")
            result_container["out"] = output
        except Exception as e:
            result_container["error"] = str(e)

    # 第一重保险：防止 exec_command 卡死
    for i in range(10):
        t = threading.Thread(target=run_cmd)
        t.start()
        t.join(timeout=6)

        if t.is_alive():
            print("glitch进程检查失败: exec_command 卡死 (可能目标机死机)")
            ssh = None
            return "dead"

        if "error" in result_container:
            print(f"glitch进程检查失败: {result_container['error']}")
            ssh = None
            return "dead"

        output = result_container.get("out", "")
        if output:  
            # pgrep 找到 PID（进程在运行）
            # print(f"glitch进程在运行, PID={output}")
            return "running"
        else:
            # pgrep 没找到进程
            time.sleep(0.5)
    print("--------------------glitch进程未运行--------------------------")
    Unexpected_death = True
    return "Unexpected_death"


def connect_DCpower():
    global DCPower_resourceManager, DC_session, DCPower_ADDRESS
    try:
        if DCPower_resourceManager is None:
            DCPower_resourceManager = visa.ResourceManager()
        if DC_session is None:
            DC_session = DCPower_resourceManager.open_resource(DCPower_ADDRESS)
        if DC_session.resource_name.startswith('ASRL') or DC_session.resource_name.endswith('SOCKET'):
            DC_session.read_termination = '\n'
        return True
    except Exception as e:
        print(f"[connect_DCpower] 连接失败: {e}")
        DC_session = None
        sys.exit(1)

def disconnect_DCpower():
    global DCPower_resourceManager, DC_session
    DC_session.close()
    DCPower_resourceManager.close()

def close_DCpower():
    global DC_session, DC_channel1, DC_channel2
    for i in range(3):
        try:
            DC_session.clear()
            time.sleep(0.1)
            DC_session.write(f"OUTP OFF,(@{DC_channel1})")
            DC_session.write(f"OUTP OFF,(@{DC_channel2})")
            return
        except Exception as e:
            print(f"[close_DCpower] error: {e}, try to {i+1} reconnection")
            DC_session = None
            if not connect_DCpower():
                time.sleep(1)
    print("[close_DCpower] failed severel times")
    sys.exit(1) 


def remote_ctr(duration):
    global DC_session, DC_channel4
    for i in range(3):
        try:
            DC_session.clear()
            DC_session.write(f"OUTP ON,(@{DC_channel4})")
            time.sleep(duration)
            DC_session.write(f"OUTP OFF,(@{DC_channel4})")
            return
        except Exception as e:
            print(f"[remote_ctr] 出错: {e}, 尝试第 {i+1} 次重连")
            DC_session = None
            if not connect_DCpower():
                time.sleep(1)
    print("[remote_ctr] 多次重试失败，放弃")
    sys.exit(1) 


def remote_rst():
    global restart
    print("主机死机，强制关机")
    time.sleep(1)
    close_DCpower()
    time.sleep(1)
    remote_ctr(6)
    time.sleep(1)
    print("开机")
    time.sleep(0.1)
    remote_ctr(0.3)
    time.sleep(180)
    restart = True


def mul():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 2
    freq = 2.0
    step = 0.3

    freq_glitch = {2.0:0.6, 1.7:0.053, 1.4:0.060, 1.1:0.075, 0.8:0.085}


    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/memory-access && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/memory-access && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None
                count += 1
                if count == 5:
                    count = 0
                    freq = round(freq - step, 1)
                if freq < 0.8:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("结束退出")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(MUL_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        pre_volt = freq_glitch.get(freq) - 0.020
                        # cfg_DCpower_ch1_volt(pre_volt)
                        fault_volt = freq_glitch.get(freq)
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz下第 {count} 次启动进程")
                        ssh.exec_command(f"cd /home/xxx/voltpillager/poc/mul && sudo ./run.sh 5 {freq}GHz {pre_volt} {0.000100} {fault_volt} {0.000500} {0.000100}")
                        wait_log = True
                        time.sleep(CHECK_INTERVAL)
                        wait_log = True
                        restart = False
                        time.sleep(CHECK_INTERVAL)
                    else:
                        prev_state = "WAIT"
                        wait_log = False
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()




def memory_access_vddq():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False
    index = 0
    count = 0
    freq = 0.8
    step = 0.3
    fault_width = 0.000050
    pre_width = 0.000010
    # pre_width = 0


    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/memory-access && mv log.txt log_{freq}GHz_{index}_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/memory-access && mv log.txt log_{freq}GHz_{index}_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if count > 20:
                #     count = 0
                # index = index + 1
                # if index > 5:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("结束退出")
                    return
                prev_state = "OK"
            else:
                ret = is_process_running(MEMORY_ACCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        # for undervolt
                        DC_volt = 0.12
                        pre_volt = 0.12
                        # pre_width = 0
                        #for overvolt
                        # DC_volt = 0
                        # pre_volt = 0                       
                        fault_volt = 0.250
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz {index} index下第 {count} 次启动进程")
                        ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/memory-access && sudo ./memory_test 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} {index}")
                        wait_log = True
                        restart = False
                        time.sleep(CHECK_INTERVAL)
                    else:
                        prev_state = "WAIT"
                        wait_log = False
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()


def memory_access_vccio():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False
    index = 0
    count = 0
    freq = 0.8
    fault_width = 0.000050
    pre_width = 0.000015


    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vccio/memory-access && mv log.txt log_{freq}GHz_{index}_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vccio/memory-access && mv log.txt log_{freq}GHz_{index}_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if count > 5:
                    # count = 0
                    # index = index + 1
                    # if index > 0:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("结束退出")
                        return
                prev_state = "OK"
            else:
                ret = is_process_running(MEMORY_ACCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        # for read
                        DC_volt = 0.21
                        pre_volt = 0.21                 
                        fault_volt = 0.350
                        # for write
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz {index} index下第 {count} 次启动进程")
                        ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vccio/memory-access && sudo ./memory_test 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} {index}")
                        wait_log = True
                        restart = False
                        time.sleep(CHECK_INTERVAL)
                    else:
                        prev_state = "WAIT"
                        wait_log = False
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()

def memory_access_vccsa():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False
    index = 0
    count = 0
    freq = 0.8
    fault_width = 0.000050
    pre_width = 0.000015


    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vccsa/memory-access && mv log.txt log_{freq}GHz_{index}_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vccsa/memory-access && mv log.txt log_{freq}GHz_{index}_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if count > 5:
                    count = 0
                    index = index + 1
                    if index > 0:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("结束退出")
                        return
                prev_state = "OK"
            else:
                ret = is_process_running(MEMORY_ACCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        # for undervolt
                        DC_volt = 0.10
                        pre_volt = 0.10                 
                        fault_volt = 0.15
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz {index} index下第 {count} 次启动进程")
                        ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vccsa/memory-access && sudo ./memory_test 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} {index}")
                        wait_log = True
                        restart = False
                        time.sleep(CHECK_INTERVAL)
                    else:
                        prev_state = "WAIT"
                        wait_log = False
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()


def sgx_memory_access():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 0.8
    fault_width = 0.000050
    pre_width = 0.002740


    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/sgx-memory-access && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/sgx-memory-access && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if (count % 2) == 0:
                    # count = 0
                    # freq = round(freq - step, 1)
                    pre_width = pre_width + 0.000005
                    # fault_width = fault_width + 0.000003
                if pre_width > 0.003100:
                # if count > 10:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("结束退出")
                        break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = 0.12
                        pre_volt = 0.12
                        fault_volt = 0.280
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz下第 {count} 次启动进程")
                        ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/sgx-memory-access && sudo ./app 50 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} 0")
                        wait_log = True
                        restart = False
                        time.sleep(CHECK_INTERVAL)
                    else:
                        prev_state = "WAIT"
                        wait_log = False
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()

def sgx_memory_SHA512():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 0.8
    fault_width = 0.000050
    pre_width = 0.1530


    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/sgx-SHA512-IPP && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/sgx-SHA512-IPP && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if (count % 2) == 0:
                    # count = 0
                    # freq = round(freq - step, 1)
                    pre_width = pre_width + 0.000005
                    # fault_width = fault_width + 0.000003
                if pre_width > 0.3:
                # if count > 10:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("结束退出")
                        break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = 0.12
                        pre_volt = 0.12
                        fault_volt = 0.335
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz下第 {count} 次启动进程")
                        ssh.exec_command(f"cd /home/xxx/voltpillager/poc/fault-vddq/sgx-SHA512-IPP && sudo ./app 50 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} 0")
                        wait_log = True
                        restart = False
                        time.sleep(CHECK_INTERVAL)
                    else:
                        prev_state = "WAIT"
                        wait_log = False
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()



if __name__ == "__main__":
    # sgx_sm4()
    # sgx_SIMD()
    # memory_access_vddq()
    # sgx_memory_access()
    # memory_access_vccio()
    # memory_access_vccsa()
    # mul()
    sgx_memory_SHA512()
    