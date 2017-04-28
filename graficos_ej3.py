# Graficos del ejercicio 3 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

masa_percolante = np.loadtxt("tp1_3.txt")
L = range(2,8)
for i in range(6):
    L[i] = L[i]**2

#==============================================================================
# rho = []
# for i in range(6):
#     rho.append(masa_percolante[i]/L[i])
#     
# plt.plot(L,rho)
#==============================================================================

log_mp = np.log(masa_percolante)
log_L = np.log(L)
    
plt.plot(log_L,log_mp)

ajuste = np.polyfit(log_L,log_mp,1,full=True)
#==============================================================================
# x_ajuste = np.linspace(log_L[0],log_L[-1],100)
# y_ajuste = ajuste[1] + x_ajuste*ajuste[0]
# plt.plot(x_ajuste,y_ajuste,"r")
# plt.xlabel("log(L)")
# plt.ylabel("log(M)")
# 
# plt.show()
#==============================================================================

print ajuste
