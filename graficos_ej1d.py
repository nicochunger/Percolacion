# Graficos del ejercicio 1d de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

# Imoprta los datos
n = 512
nombre_archivo = "ns_" + str(n) + "_10000.txt"
ns = np.loadtxt(nombre_archivo)
s = range(n*n)

log_ns = np.log(ns)
log_s = np.log(s)

plt.plot(log_s,log_ns)

start = int(np.exp(3))
final = int(np.exp(5))

x_fiteo = log_s[start:final]
y_fiteo = log_ns[start:final]

#plt.plot(x_fiteo,y_fiteo)
ajuste = np.polyfit(x_fiteo,y_fiteo,1)

print ajuste


