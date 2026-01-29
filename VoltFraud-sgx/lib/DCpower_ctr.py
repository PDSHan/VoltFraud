from paramiko import SSHClient, client
import time
import pyvisa as visa
import sys
import serial

DCPower_ADDRESS = 'TCPIP::10.42.0.83::INSTR'
DCPower_resourceManager = None
DC_session = None
DC_channel = "1"


def connect():
    global DCPower_resourceManager, DC_session, DCPower_ADDRESS
    if DCPower_resourceManager==None or DC_session==None:
        # Create a connection (session) to the TCP/IP socket on the instrument.
        DCPower_resourceManager = visa.ResourceManager()
        DC_session = DCPower_resourceManager.open_resource(DCPower_ADDRESS)
    if DC_session.resource_name.startswith('ASRL') or DC_session.resource_name.endswith('SOCKET'):
        DC_session.read_termination = '\n'

def disconnect():
    global DCPower_resourceManager, DC_session
    DC_session.close()
    DCPower_resourceManager.close()

def cfg_glitch_type1(fault_volt):
    global DC_session, DC_channel
    # global DC_session
    DC_session.clear()
    DC_session.write(f"VOLT {fault_volt},(@{DC_channel})")

def cfg_glitch_type2(pre_volt, pre_width, fault_volt, fault_width, tag):
    global DC_session, DC_channel
    DC_session.clear()
    DC_session.write(f"ARB:FUNC:TYPE VOLT,(@{DC_channel})")
    DC_session.write(f"ARB:FUNC:SHAP UDEF,(@{DC_channel})")
    if tag == 0:
        DC_session.write(f"ARB:VOLT:UDEF:LEV {round(fault_volt, 4)},(@{DC_channel})")
        DC_session.write(f"ARB:VOLT:UDEF:DWEL {round(fault_width, 6)},(@{DC_channel})")
    else:
        DC_session.write(f"ARB:VOLT:UDEF:LEV {round(pre_volt, 6)},{round(fault_volt, 4)},(@{DC_channel})")
        DC_session.write(f"ARB:VOLT:UDEF:DWEL {round(pre_width, 6)},{round(fault_width, 6)},(@{DC_channel})")

def set_BNC_Trigger(repeat):
    global DC_session, DC_channel
    DC_session.clear()
    DC_session.write(f"VOLT:MODE ARB,(@{DC_channel})")
    DC_session.write("TRIG:ARB:SOUR EXT")
    # DC_session.write(f"VOLT 0.0,(@{DC_channel})")
    DC_session.write(f"OUTP ON,(@{DC_channel})")
    if repeat:
        DC_session.write(f"INITiate:CONTinuous:TRANsient ON,(@{DC_channel})")
    else:  
        DC_session.write(f"INIT:TRAN (@{DC_channel})")
    ret = DC_session.query(f"STAT:OPER:COND? (@{DC_channel})")
    while True:
        try:
            val = int(ret)
        except ValueError:
            # print(f"返回的不是数字: {ret}")
            time.sleep(0.1)
            continue
        if val & 0x10:
            print(f"device is ready to receive trigger signal. return is {val}.")
            break
        else:
            print(f"device is not ready to receive trigger signal. return is {val}.")
            time.sleep(0.1)  # 避免死循环占满 CPU

def ctr_DC_channel(cmd):
    global DC_session,DC_channel
    DC_session.clear()
    DC_session.write(f"OUTP {cmd},(@{DC_channel})")


def close_BNC_Arb():
    global DC_session, DC_channel
    DC_session.clear()
    DC_session.write(f"OUTP OFF,(@{DC_channel})")
    DC_session.write(f"INITiate:CONTinuous:TRANsient OFF,(@{DC_channel})")
    time.sleep(0.1)
    ser = serial.Serial("/dev/ttyS0", 115200, timeout=1)
    ser.dtr = False
    ser.close()
    ret = DC_session.query(f"STAT:OPER:COND? (@{DC_channel})")
    while True:
        try:
            val = int(ret)
        except ValueError:
            # print(f"返回的不是数字: {ret}")
            time.sleep(0.1)
            continue
        if val & 0x40:
            time.sleep(0.1)
            # print(ret)
            ret = DC_session.query(f"STAT:OPER:COND? (@{DC_channel})")
        else:
            # print(ret)
            return   



if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 script.py <arg1> [arg2]")
        sys.exit(1)

    arg1 = sys.argv[1]   # 第一个参数
    if arg1 == "cfg_type1":
        fault_volt = float(sys.argv[2])
        connect()
        cfg_glitch_type1(fault_volt)
        disconnect()
    elif arg1 == "cfg_type2":
        pre_volt = float(sys.argv[3])
        pre_width = float(sys.argv[4])
        fault_volt = float(sys.argv[5])
        fault_width = float(sys.argv[6])
        tag = int(sys.argv[7])
        repeat = True if int(sys.argv[2])>0 else False
        connect()
        cfg_glitch_type2(pre_volt, pre_width, fault_volt, fault_width, tag)
        time.sleep(0.1)
        set_BNC_Trigger(repeat)
        disconnect()
    elif arg1 == "cfg_type3":
        fault_volt = float(sys.argv[2])
        connect()
        cfg_glitch_type1(fault_volt)
        disconnect()
    elif arg1 == "cmd":
        connect()
        cmd = sys.argv[2]
        ctr_DC_channel(cmd)
        disconnect()
    elif arg1 == "close_BNC_Arb":
        connect()
        close_BNC_Arb()
        disconnect()
    else:
        print("非法参数")
        sys.exit(1)
