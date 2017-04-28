# Programa que hace los graficos para el ejercicio 2 de la guia 1 de percolacion

import numpy as np
import matplotlib.pyplot as plt

intensidad = np.loadtxt("tp1_2_128.txt")
probas = np.loadtxt("vector_probabilidades.txt")

log_int = np.log(intensidad[600:])
log_p = np.log(probas[600:]-0.5926)

ajuste = np.polyfit(log_p,log_int,1,full=True)

#==============================================================================
# x_fit = np.linspace(log_p[0],log_p[-1],100)
# y_fit = ajuste[1] + ajuste[0]*x_fit
# 
# plt.plot(log_p,log_int)
# plt.plot(x_fit,y_fit,"r")
# plt.xlabel("log(p-pc)")
# plt.ylabel("log(P)")
# plt.show()
#==============================================================================
print ajuste

#==============================================================================
# plt.plot(probas,intensidad)
# plt.xlabel("p")
# plt.ylabel("Intensidad")
# 
#==============================================================================
