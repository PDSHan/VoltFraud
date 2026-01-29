import serial
import time

# Linux 示例：/dev/ttyUSB0
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=115200,
    timeout=1
)

while True:
    ser.setDTR(True)
    print("DTR = HIGH")
    time.sleep(1)

    ser.setDTR(False)
    print("DTR = LOW")
    time.sleep(1)

ser.close()
