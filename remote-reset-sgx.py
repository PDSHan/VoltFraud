import paramiko
import time
import sys
from datetime import datetime, timedelta
import threading
import pyvisa as visa

REMOTE_HOST = "10.42.0.84"
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
Unexpected_death = False

ssh = None
DCpower = None

def ssh_connect():
    global ssh
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(REMOTE_HOST, username=USERNAME, password=PASSWORD, timeout=5)
        print("SSH connect")
    except Exception as e:
        print(f"SSH failed: {e}")
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
            deadline = time.time() + 5  
            output = []
            while time.time() < deadline:
                if stdout.channel.exit_status_ready():
                    output = stdout.read().decode().strip()
                    break
                time.sleep(0.1)
            else:
                raise TimeoutError("stdout.read() timeout")
            result_container["out"] = output
        except Exception as e:
            result_container["error"] = str(e)

    t = threading.Thread(target=run_cmd)
    t.start()
    t.join(timeout=6) 

    if t.is_alive():
        print("failed")
        # ssh.close()
        ssh = None
        return False
    if "error" in result_container:
        print(f"failed:: {result_container['error']}")
        ssh = None
        return False
    if result_container.get("out") == "ok":
        return True
    else:
        ssh = None
        print(f"failed, {result_container.get('out')}")
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
            deadline = time.time() + 5
            output = None
            while time.time() < deadline:
                if stdout.channel.exit_status_ready():
                    output = stdout.read().decode().strip()
                    break
                time.sleep(0.1)
            else:
                raise TimeoutError("stdout.read() timeout")
            result_container["out"] = output
        except Exception as e:
            result_container["error"] = str(e)

    # def run_cmd():
    #     try:
    #         stdin, stdout, stderr = ssh.exec_command(f"pgrep -x {program_name}")
    #         pid = stdout.read().decode().strip()
    #         if not pid:
    #             result_container["error"] = "not_alive"
    #             return

    #         stdin, stdout, stderr = ssh.exec_command(
    #             f"awk '/^State:/ {{print $2}}' /proc/{pid}/status 2>/dev/null"
    #         )
    #         state = stdout.read().decode().strip()

    #         if state in ("R", "S", "D"):
    #             result_container["out"] = pid
    #         else:
    #             result_container["error"] = "not_alive"
    #     except Exception as e:
    #         result_container["error"] = str(e)

    for i in range(10):
        t = threading.Thread(target=run_cmd)
        t.start()
        t.join(timeout=6)

        if t.is_alive():
            print("glitch failed: exec_command")
            ssh.close()
            ssh = None
            return "dead"

        if "error" in result_container:
            print(f"failed: {result_container['error']}")
            ssh.close()
            ssh = None
            return "dead"

        output = result_container.get("out", "")
        if output:  
            return "running"
        else:
            time.sleep(0.5)
    print("--------------------glitch no running--------------------------")
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
        print(f"[connect_DCpower] failed: {e}")
        DC_session = None
        sys.exit(1)

def disconnect_DCpower():
    global DCPower_resourceManager, DC_session
    DC_session.close()
    DCPower_resourceManager.close()

def close_DCpower():
    global DC_session, DC_channel1
    for i in range(3):
        try:
            DC_session.clear()
            time.sleep(0.1)
            DC_session.write(f"OUTP OFF,(@{DC_channel1})")
            return
        except Exception as e:
            print(f"[close_DCpower] error")
            DC_session = None
            if not connect_DCpower():
                time.sleep(1)
    print("[close_DCpower]")
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
            print(f"[remote_ctr] error")
            DC_session = None
            if not connect_DCpower():
                time.sleep(1)
    print("[remote_ctr] failed too many")
    sys.exit(1) 


def remote_rst():
    global restart
    close_DCpower()
    time.sleep(0.1)
    remote_ctr(6)
    print("reset!")
    time.sleep(0.1)
    remote_ctr(0.3)
    time.sleep(30)
    restart = True


def mul():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 2
    freq = 1.4
    step = 0.3

    freq_glitch = {3.8:0.043, 3.5:0.053, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}
  # freq_glitch = {3.8:0.032, 3.5:0.042, 3.2:0.057, 2.9:0.072, 2.6:0.089, 2.3:0.095, 2.0:0.106, 1.7:0.113, 1.4:0.123, 1.1:0.132, 0.8:0.144}

    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()

        else:
            if prev_state == "WAIT":
                ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/mul && mv log.txt log_{freq}GHz_{count}.txt")
                count += 1
                if count == 5:
                    count = 0
                    freq = round(freq - step, 1)
                if freq < 0.8:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(MUL_PROCESS)
                if ret == "not_running":
                    if wait_log == False:
                        pre_volt = freq_glitch.get(freq) - 0.020
                        # cfg_DCpower_ch1_volt(pre_volt)
                        fault_volt = freq_glitch.get(freq)
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/mul && sudo ./run.sh 5 {freq}GHz {pre_volt} {0.000100} {fault_volt} {0.000500} {0.000100}")
                        wait_log = True
                        time.sleep(CHECK_INTERVAL)
                    else:
                        wait_log = False
                        prev_state = "WAIT"
                elif ret == "running":
                    time.sleep(CHECK_INTERVAL)
                elif ret =="dead":
                    remote_rst()


def sgx_mul():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 3.8
    step = 0.3

    freq_glitch = {3.8:0.043, 3.5:0.053, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}
    
    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-mul && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-mul && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                if count == 5:
                    count = 0
                    freq = round(freq - step, 1)
                if freq < 0.8:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        pre_volt = freq_glitch.get(freq) - 0.020
                        fault_volt = freq_glitch.get(freq)
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-mul && sudo ./run.sh 10 {freq}GHz {pre_volt} 0.000100 {fault_volt} 0.000500 0.000100")
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


def sgx_rsa():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 3.8
    step = 0.3

    freq_glitch = {3.8:0.043, 3.5:0.053, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}
    
    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-crt-rsa && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-crt-rsa && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                if count == 5:
                    count = 0
                    freq = round(freq - step, 1)
                if freq < 0.8:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_pre_volt = freq_glitch.get(freq) - 0.020
                        pre_volt = freq_glitch.get(freq)- 0.005
                        fault_volt = freq_glitch.get(freq) + 0.015
                        fault_delay = 0.000050 + (3.8-freq)/step * 0.000005
                        delay = 0
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-crt-rsa && sudo ./run.sh 10000 {freq}GHz {DC_pre_volt} {pre_volt} 0.000040 {fault_volt} {fault_delay} {delay}")
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


def sgx_SHA512():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 3.8
    step = 0.3
    # delay = 0.000020

    freq_glitch = {3.8:0.043, 3.5:0.050, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}

    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-SHA512-IPP && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-SHA512-IPP && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                if (count % 5) == 0:
                    count = 0
                    freq = round(freq - step, 1)
                    # delay = delay + 0.000001
                if freq < 0.8:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = freq_glitch.get(freq) - 0.020
                        pre_volt = freq_glitch.get(freq)
                        pre_width = 0.000020
                        fault_volt = freq_glitch.get(freq) + 0.030
                        fault_delay = 0.000050 + (3.8-freq)/step * 0.000001
                        delay = 0
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-SHA512-IPP && sudo ./app 1000 {freq}GHz {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_delay} {delay}")
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


def sgx_HMAC():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 3.8
    step = 0.3
    pre_width = 0.000020

    freq_glitch = {3.8:0.043, 3.5:0.050, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}

    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-hmac && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-hmac && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                if (count % 5) == 0:
                    pre_width += 0.000001
                    if pre_width > 0.000030:
                        freq = round(freq - step, 1)
                        count = 0
                if freq < 1.5:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = freq_glitch.get(freq) - 0.020
                        pre_volt = freq_glitch.get(freq)
                        fault_volt = freq_glitch.get(freq) + 0.030
                        fault_delay = 0.000050 + (3.8-freq)/step * 0.000001
                        delay = 0
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-hmac && sudo ./app 1000 {freq}GHz {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_delay} {delay}")
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


def sgx_sm4():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 2.9
    step = 0.3
    fault_delay = 0.000044
    pre_width = 0.000025

    freq_glitch = {3.8:0.043, 3.5:0.050, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}

    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-sm4 && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-sm4 && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                # if (count % 5) == 0:
                #     fault_delay += 0.000001
                #     if fault_delay > 0.000065:
                #         fault_delay = 0.000041
                #         count = 0
                #         # pre_width += 0.000001
                #         freq = round(freq - step, 1)
                if freq < 2.1:
                # if pre_width > 0.000050:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = freq_glitch.get(freq) - 0.020
                        pre_volt = freq_glitch.get(freq)
                        fault_volt = freq_glitch.get(freq) + 0.010
                        delay = 0
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-sm4 && sudo ./app 1000 {freq}GHz {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_delay} {delay}")
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


def sgx_SIMD():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 2.9
    step = 0.3
    fault_delay = 0.000065
    pre_width = 0.000025

    freq_glitch = {3.8:0.043, 3.5:0.050, 3.2:0.060, 2.9:0.075, 2.6:0.085, 2.3:0.095, 2.0:0.102, 1.7:0.112, 1.4:0.118, 1.1:0.128, 0.8:0.144}

    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-SIMD && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-SIMD && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                # if (count % 5) == 0:
                #     fault_delay += 0.000001
                #     if fault_delay > 0.000065:
                #         fault_delay = 0.000041
                #         count = 0
                #         # pre_width += 0.000001
                #         freq = round(freq - step, 1)
                if freq < 2.1:
                # if pre_width > 0.000050:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = freq_glitch.get(freq) - 0.020
                        pre_volt = freq_glitch.get(freq)
                        fault_volt = freq_glitch.get(freq) + 0.060
                        delay = 0
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-SIMD && sudo ./app 1000 {freq}GHz {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_delay} {delay}")
        
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


def sgx_EdDSA():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 3.8
    step = 0.3
    fault_delay = 0.000070
    pre_width = 0.000035

    freq_glitch = {3.8:0.043, 3.5:0.050, 3.2:0.060, 2.9:0.075, 2.6:0.095, 2.3:0.105, 2.0:0.115, 1.7:0.125, 1.4:0.135, 1.1:0.145, 0.8:0.145}

    connect_DCpower()
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-EdDSA && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-EdDSA && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                count += 1
                if (count % 3) == 0:
                    # fault_delay += 0.000001
                #     if fault_delay > 0.000065:
                #         fault_delay = 0.000041
                    count = 0
                    freq = round(freq - step, 1)
                if freq < 0.8:
                # if fault_delay > 0.000100:
                    disconnect_DCpower()
                    ssh_disconnect()
                    print("exit")
                    break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        pre_volt = freq_glitch.get(freq) - 0.025
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/sgx-EdDSA && sudo ./app 5 {freq}GHz 0 {pre_volt} 0 0 0 0")
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


def memory_access_mc():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False
    index = 0
    count = 0
    freq = 0.8

    pre_width = 0.000025

    # fault_width = 0.000050
    fault_width = 0.000070

    connect_DCpower()

    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-mc/memory-access && mv log.txt log_{freq}GHz_{index}_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-mc/memory-access && mv log.txt log_{freq}GHz_{index}_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if count > 5:
                    count = 0
                    index = index + 1
                    if index > 511:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("exit")
                        break
                prev_state = "OK"
            else:
                ret = is_process_running(MEMORY_ACCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        # for undervolt
                        DC_volt = 0.1530
                        pre_volt = 0.1530                 
                        # fault_volt = 0.3520
                        fault_volt = 0.300
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz {index} run at {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-mc/memory-access && sudo ./memory_test 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} {index}")
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


def sgx_memory_access_mc():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False

    count = 0
    freq = 0.8
    pre_width = 0.001750
    fault_width = 0.000200

    connect_DCpower()
    
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-mc/sgx-memory-access && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-mc/sgx-memory-access && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                count += 1
                # if (count % 3) == 0:
                #     # count = 0
                #     # freq = round(freq - step, 1)
                #     fault_width = fault_width + 0.000001
                # if fault_width > 0.000070:
                if count > 100:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("exit")
                        break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = 0.1530
                        pre_volt = 0.1530
                        fault_volt = 0.20
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-mc/sgx-memory-access && sudo ./app 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} 0")
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


def memory_access_sa():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False
    index = 0
    count = 0
    freq = 0.8
    pre_width = 0.000015    
    fault_width = 0.000050

    connect_DCpower()

    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-sa/memory-access && mv log.txt log_{freq}GHz_{index}_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-sa/memory-access && mv log.txt log_{freq}GHz_{index}_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                    remote_rst()
                    restart = True
                    ssh = None

                count += 1
                if count > 5:
                    count = 0
                    index = index + 1
                    if index > 3:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("exit")
                        break
                prev_state = "OK"
            else:
                ret = is_process_running(MEMORY_ACCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = 0.35
                        pre_volt = 0.35
                        fault_volt = 0.570
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz {index} run at {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-sa/memory-access && sudo ./memory_test 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} {index}")
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



def sgx_memory_access_sa():
    global ssh, restart, Unexpected_death
    prev_state = "OK"
    wait_log = False
    count = 0
    freq = 0.8
    # time params for read
    # pre_width = 0.001750
    # fault_width = 0.000200

    # time params for write
    pre_width = 0.00040
    fault_width = 0.00050

    connect_DCpower()
    
    while True:
        if not is_host_alive():
                remote_rst()
                restart = True
        else:
            if prev_state == "WAIT":
                if not Unexpected_death:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-sa/sgx-memory-access && mv log.txt log_{freq}GHz_{count}.txt")
                else:
                    ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-sa/sgx-memory-access && mv log.txt log_{freq}GHz_{count}_Unexpect.txt")
                    Unexpected_death = False
                    time.sleep(10)
                count += 1
                if count > 100:
                        disconnect_DCpower()
                        ssh_disconnect()
                        print("exit")
                        break
                prev_state = "OK"
            else:
                ret = is_process_running(SGX_PROCESS)
                if ret == "not_running" or ret == "Unexpected_death":
                    if ret == "Unexpected_death":
                        Unexpected_death=True
                    if wait_log == False:
                        DC_volt = 0.35
                        pre_volt = 0.35
                        fault_volt = 0.370
                        now = datetime.now()
                        print(f"\n{now.strftime("%H:%M:%S")}, {freq} GHz run {count}th")
                        ssh.exec_command(f"cd /home/xxx/VoltFraud-sgx/poc/fault-sa/sgx-memory-access && sudo ./app 10 {freq} {DC_volt} {pre_volt} {pre_width} {fault_volt} {fault_width} 0")
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
    # sgx_HMAC()
    #TODO reset DCpower connection
    # sgx_sm4()
    # sgx_SIMD()
    # memory_access_mc()
    sgx_memory_access_mc()
    # memory_access_sa()
    # sgx_memory_access_sa()
