# Graficos del ejercicio 5 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

y = np.loadtxt("tp1_5_pmax.txt")
x = range(16)

log_x = np.log(x)
log_y = np.log(abs(y-0.592510))

plt.plot(log_x,log_y)

ajuste = np.polyfit(log_x[1:],log_y[1:],1)
print ajuste