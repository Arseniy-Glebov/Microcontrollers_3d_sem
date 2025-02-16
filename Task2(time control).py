import serial

ser = serial.Serial('COM6', 195200)

while(True):
    t = int(input("please, enter the time: "))
    ser.write(bytes(str(t)[::-1] + '`', 'utf-8'))
    # print(str(t)[::-1] + '`')
    ser.readline().decode('utf-8')
