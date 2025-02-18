import serial
ser = serial.Serial('/dev/ttyACM0')
ser.write(b'1')
print(ser.read())
ser.close()
