# Graficos del ejercicio 3 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

masa_percolante = np.loadtxt("tp1_3.txt")
L = range(2,8)
for i in range(6):
    L[i] = L[i]**2
    
log_mp = np.log(masa_percolante)
log_L = np.log(L)
    
plt.plot(log_L,log_mp,"k")

ajuste = np.polyfit(log_L,log_mp,1)
x_ajuste = np.linspace(log_L[0],log_L[-1],100)
y_ajuste = ajuste[1] + x_ajuste*ajuste[0]
plt.plot(x_ajuste,y_ajuste,"r")

plt.show()

print ajuste