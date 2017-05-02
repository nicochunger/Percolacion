# Graficos del ejercicio 6 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt
from operator import sub

m2_6 = np.loadtxt("tp1_6_m2_6.txt")
m2 = np.loadtxt("tp1_6_m2_128.txt")
p_6 = np.loadtxt("tp1_6_probas_6.txt")
p = np.loadtxt("tp1_6_probas_128.txt")

ind_max = np.argmax(m2)
print ind_max

gamma_menos = [] #Gamma obtenidos del lado izquierdo
gamma_mas = [] #Gammas obtenidos del lado derecho

rango = 50
pts_gamma = ind_max-5-rango

for i in range(pts_gamma):
    ajuste1 = np.polyfit(np.log(abs(p[i:rango+i]-0.5926)),np.log(m2[i:rango+i]),1)
    ajuste2 = np.polyfit(np.log(abs(p[ind_max+pts_gamma-i:ind_max+pts_gamma+rango-i]-0.5926)),np.log(m2[ind_max+pts_gamma-i:ind_max+pts_gamma+rango-i]),1)
    gamma_menos.append(ajuste1[0])
    gamma_mas.append(ajuste2[0])

diferencia = np.abs(map(sub, gamma_menos, gamma_mas))
minimo = np.argmin(diferencia)
gamma = np.average([gamma_menos[minimo],gamma_mas[minimo]])
print gamma, minimo
    
plt.plot(gamma_menos,"b.")
plt.plot(gamma_mas,"r.")
plt.xlabel("Indice del rango utilizado")
plt.ylabel(r"$\gamma$")
plt.legend((r"$\gamma^-$", r"$\gamma^+$"),loc=2)
plt.grid(b=True, which='both', color='0.65',linestyle='-')
plt.show()

#==============================================================================
# plt.figure(figsize=(6,7))
# 
# ax = plt.subplot(211)
# ax.set_title("L=6")
# ax.plot(p_6,m2_6,".")
# 
# ax = plt.subplot(212)
# ax.set_title("L=128")
# ax.plot(p_128,m2_128,".")
# 
# plt.xlabel("p")
# plt.ylabel("m_2")
# 
# plt.tight_layout()
#==============================================================================


#==============================================================================
# plt.plot(p_128,m2_128,".")
# plt.xlabel("p")
# plt.ylabel(r"$m_2$")
#==============================================================================


#plt.plot(log_p,log_m2,".")
