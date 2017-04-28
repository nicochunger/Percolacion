# Graficos del ejercicio 6 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt
from operator import sub

m2 = np.loadtxt("tp1_6_m2_128.txt")
p = np.loadtxt("tp1_6_probas.txt")

ind_max = np.argmax(m2)
print ind_max

gamma_menos = [] #Gamma obtenidos del lado izquierdo
gamma_mas = [] #Gammas obtenidos del lado derecho

rango = 70
pts_gamma = ind_max-5-rango

for i in range(pts_gamma):
    ajuste1 = np.polyfit(np.log(abs(p[0:rango+i]-0.5926)),np.log(m2[0:rango+i]),1)
    ajuste2 = np.polyfit(np.log(abs(p[ind_max+pts_gamma-i:ind_max+pts_gamma+rango]-0.5926)),np.log(m2[ind_max+pts_gamma-i:ind_max+pts_gamma+rango]),1)
    gamma_menos.append(ajuste1[0])
    gamma_mas.append(ajuste2[0])

diferencia = map(sub, gamma_menos, gamma_mas)
minimo = np.argmin(diferencia)
gamma = np.average([gamma_menos[minimo],gamma_mas[minimo]])
print gamma
    
plt.plot(gamma_menos,"b.")
plt.plot(gamma_mas,"r.")
plt.show()

#plt.plot(p,m2,".")
#plt.plot(log_p,log_m2,".")
