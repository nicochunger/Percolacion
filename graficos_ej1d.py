# Graficos del ejercicio 1d de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

# Imoprta los datos
n = 128
nombre_archivo = "ns_" + str(n) + "_100000.txt"
ns = np.loadtxt(nombre_archivo)
print len(ns)
s = range(n*n)

log_ns = np.log(ns)
log_s = np.log(s)

plt.plot(log_s,log_ns)

start = int(np.exp(2))
final = int(np.exp(5))

x_fiteo = log_s[start:final]
y_fiteo = log_ns[start:final]

#plt.plot(x_fiteo,y_fiteo)
ajuste = np.polyfit(x_fiteo,y_fiteo,1,full=True)
plt.xlabel("log(s)")
plt.ylabel("log(n_s(pc))")

print ajuste



