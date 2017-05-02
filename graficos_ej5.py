# Graficos del ejercicio 5 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

y = np.loadtxt("tp1_5_pmax.txt")
x = range(16)

log_x = np.log(x)
log_y = np.log(abs(y-0.592510))

plt.plot(log_x,log_y)

ajuste = np.polyfit(log_x[1:],log_y[1:],1)

x_fit = np.linspace(log_x[1],log_x[-1])
y_fit = ajuste[1] + ajuste[0]*x_fit

plt.plot(x_fit,y_fit,"r")
plt.xlabel("log(s)")
plt.ylabel("log(p_max - p_c)")
plt.show()
 
print ajuste