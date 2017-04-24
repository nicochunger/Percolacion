# Graficos del ejercicio 4 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

s1 = 50
s2 = 100
s3 = 200
nombre1 = "tp1_4_fz_s" + str(s1) + ".txt"
nombre2 = "tp1_4_fz_s" + str(s2) + ".txt"
nombre3 = "tp1_4_fz_s" + str(s3) + ".txt"

f1 = np.loadtxt(nombre1)
f2 = np.loadtxt(nombre2)
f3 = np.loadtxt(nombre3)

p = np.loadtxt("tp1_4_probas.txt")
    
z1 = s1**(float(36)/91)*((p-0.592510)/0.592510)
z2 = s2**(float(36)/91)*((p-0.592510)/0.592510)
z3 = s3**(float(36)/91)*((p-0.592510)/0.592510)

#indice_0 = np.argmin(abs(z))
#print f[indice_0]

plt.plot(z1,f1,"b")
plt.plot(z2,f2,"r")
plt.plot(z3,f3,"g")
plt.show()