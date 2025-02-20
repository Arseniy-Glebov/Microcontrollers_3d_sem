import serial
import matplotlib.pyplot as plt

ser = serial.Serial('COM6', 195200)

time = []
raw = []
volt = []

n = int(input("print number of points(positive integer) to start collecting data: "))

ser.write(bytes("START\n", 'utf-8'))
print(ser.readline().decode('utf-8'))

for i in range(n):
    ser.write(bytes("PROCEED\n", 'utf-8'))
    raw.append(ser.readline().decode('utf-8'))

ser.write(bytes("STOP\n", 'utf-8'))

for i, elem in enumerate(raw):
    time.append(float(elem.split(" ")[1][:-1]) / 1000)
    volt.append(float(elem.split(" ")[6]))

plt.plot(time, volt, marker='.', linewidth=0.5)

plt.xlabel("t, sec")
plt.ylabel("U, V")
plt.title(label="U(t)", loc="center")
plt.grid()

plt.show()
