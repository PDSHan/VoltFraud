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

def cfg_glitch_type1(fault_volt, channel):
    # global DC_session, DC_channel
    global DC_session
    DC_session.clear()
    DC_session.write(f"VOLT {fault_volt},(@{channel})")

def cfg_glitch_type2(pre_volt, pre_width, fault_volt, fault_width, tag, channel):
    # global DC_session, DC_channel
    global DC_session
    DC_session.clear()
    DC_session.write(f"ARB:FUNC:TYPE VOLT,(@{channel})")
    DC_session.write(f"ARB:FUNC:SHAP UDEF,(@{channel})")
    if tag == 0:
        DC_session.write(f"ARB:VOLT:UDEF:LEV {round(fault_volt, 4)},(@{channel})")
        DC_session.write(f"ARB:VOLT:UDEF:DWEL {round(fault_width, 6)},(@{channel})")
    else:
        DC_session.write(f"ARB:VOLT:UDEF:LEV {round(pre_volt, 6)},{round(fault_volt, 4)},(@{channel})")
        DC_session.write(f"ARB:VOLT:UDEF:DWEL {round(pre_width, 6)},{round(fault_width, 6)},(@{channel})")

def set_BNC_Trigger(repeat, channel):
    # global DC_session, DC_channel
    global DC_session
    DC_session.clear()
    DC_session.write(f"VOLT:MODE ARB,(@{channel})")
    DC_session.write("TRIG:ARB:SOUR EXT")
    # DC_session.write(f"VOLT 0.0,(@{DC_channel})")
    DC_session.write(f"OUTP ON,(@{channel})")
    if repeat:
        DC_session.write(f"INITiate:CONTinuous:TRANsient ON,(@{channel})")
    else:  
        DC_session.write(f"INIT:TRAN (@{channel})")
    ret = DC_session.query(f"STAT:OPER:COND? (@{channel})")
    while True:
        try:
            val = int(ret)
        except ValueError:
            time.sleep(0.1)
            continue
        if val & 0x10:
            print(f"device is ready to receive trigger signal. return is {val}.")
            break
        else:
            print(f"device is not ready to receive trigger signal. return is {val}.")
            time.sleep(0.1) 
def ctr_DC_channel(cmd, channel):
    # global DC_session,DC_channel
    global DC_session
    DC_session.clear()
    DC_session.write(f"OUTP {cmd},(@{channel})")


def close_BNC_Arb(channel):
    # global DC_session, DC_channel
    global DC_session
    DC_session.clear()
    DC_session.write(f"OUTP OFF,(@{channel})")
    DC_session.write(f"INITiate:CONTinuous:TRANsient OFF,(@{channel})")
    time.sleep(0.1)
    ser = serial.Serial("/dev/ttyS0", 115200, timeout=1)
    ser.dtr = False
    ser.close()
    ret = DC_session.query(f"STAT:OPER:COND? (@{channel})")
    while True:
        try:
            val = int(ret)
        except ValueError:
            time.sleep(0.1)
            continue
        if val & 0x40:
            time.sleep(0.1)
            # print(ret)
            ret = DC_session.query(f"STAT:OPER:COND? (@{channel})")
        else:
            # print(ret)
            return   



if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 script.py <arg1> [arg2]")
        sys.exit(1)

    arg1 = sys.argv[1]   
    if arg1 == "cfg_type1":
        fault_volt = float(sys.argv[2])
        channel = (sys.argv[3])
        connect()
        cfg_glitch_type1(fault_volt, channel)
        disconnect()
    elif arg1 == "cfg_type2":
        pre_volt = float(sys.argv[3])
        pre_width = float(sys.argv[4])
        fault_volt = float(sys.argv[5])
        fault_width = float(sys.argv[6])
        tag = int(sys.argv[7])
        channel = (sys.argv[8])
        repeat = True if int(sys.argv[2])>0 else False
        connect()
        cfg_glitch_type2(pre_volt, pre_width, fault_volt, fault_width, tag, channel)
        time.sleep(0.1)
        set_BNC_Trigger(repeat, channel)
        disconnect()
    elif arg1 == "cfg_type3":
        fault_volt = float(sys.argv[2])
        connect()
        cfg_glitch_type1(fault_volt)
        disconnect()
    elif arg1 == "cmd":
        channel = (sys.argv[3])
        connect()
        cmd = sys.argv[2]
        ctr_DC_channel(cmd, channel)
        disconnect()
    elif arg1 == "close_BNC_Arb":
        channel = (sys.argv[2])
        connect()
        close_BNC_Arb(channel)
        disconnect()
    else:
        print("invalid params")
        sys.exit(1)
