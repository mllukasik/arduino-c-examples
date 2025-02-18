import serial

def get_serial():
    ser = serial.Serial()
    ser.port = '/dev/ttyACM0'
    ser.baudrate = 9600
    ser.bytesize =  serial.EIGHTBITS
    ser.parity = serial.PARITY_NONE
    ser.stopbits = serial.STOPBITS_ONE
    ser.open()
    return ser

if __name__ == "__main__":
    ser = get_serial()
    print("write")
    ser.write(b'a')
    print("read")
    print(ser.read())
    ser.close()
