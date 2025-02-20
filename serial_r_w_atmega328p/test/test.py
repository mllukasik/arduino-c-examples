import serial
import sys
from random import randbytes

def get_serial(port):
    ser = serial.Serial()
    ser.port = port
    ser.baudrate = 9600
    ser.bytesize =  serial.EIGHTBITS
    ser.parity = serial.PARITY_NONE
    ser.stopbits = serial.STOPBITS_ONE
    ser.timeout = 0.1
    ser.open()
    return ser

if __name__ == "__main__":
    port = sys.argv[1]
    ser = get_serial(port)
    while True:
        b = randbytes(1)
        ser.write(b)
        c = ser.read()
        if c == b:
            break

    test_count = 1000
    lost = 0
    for i in range(test_count):
        b = randbytes(1)
        ser.write(b)
        c = ser.read()
        if b != c:
            lost += 1
    print(f"lost bytes: {lost}")
    ser.close()

