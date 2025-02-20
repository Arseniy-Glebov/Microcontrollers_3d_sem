import serial
import matplotlib.pyplot as plt

ser = serial.Serial('COM6', 195200)

time = [0]
volt = [0]

n = input("print START to start experiment: ")

ser.write(bytes("START\n", 'utf-8'))
print(ser.readline().decode('utf-8'))

while volt[-1] < 2.9:
    ser.write(bytes("PROCEED\n", 'utf-8'))
    raw = ser.readline().decode('utf-8').split(" ")
    time.append(float(raw[1][:-1]) / 1000)
    volt.append(float(raw[6]))
    print(volt[-1])

ser.write(bytes("CAP_LOW\n", 'utf-8'))

while volt[-1] > 0.5:
    ser.write(bytes("PROCEED\n", 'utf-8'))
    raw = ser.readline().decode('utf-8').split(" ")
    time.append(float(raw[1][:-1]) / 1000)
    volt.append(float(raw[6]))
    print(volt[-1])

ser.write(bytes("STOP\n", 'utf-8'))

plt.plot(time[1:], volt[1:], marker='.', linewidth=0.5)

plt.xlabel("t, sec")
plt.ylabel("U, V")
plt.title(label="U(t)", loc="center")
plt.grid()

plt.show()
