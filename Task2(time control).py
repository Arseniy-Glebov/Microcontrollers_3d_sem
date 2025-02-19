import serial

ser = serial.Serial('COM6', 195200)

while(True):
    t = int(input("please, enter the time(seconds, integer): "))
    ser.write(bytes(str(t) + '\n', 'utf-8'))
    ser.readline().decode('utf-8')
    ser.readline().decode('utf-8')
