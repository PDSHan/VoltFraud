import serial
import time


ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    timeout=1
)

while True:
    # 拉高 DTR（True = 逻辑 1）
    ser.setDTR(True)
    print("DTR = HIGH")
    time.sleep(1)

    # 拉低 DTR（False = 逻辑 0）
    ser.setDTR(False)
    print("DTR = LOW")
    time.sleep(1)

ser.close()
