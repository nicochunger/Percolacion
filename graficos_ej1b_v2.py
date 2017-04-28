# Programa que hace los graficos para el ejercicio 2 de la guia 1 de percolacion

import numpy as np
import matplotlib.pyplot as plt

# Imoprta los datos
int1 = np.loadtxt("tp1_1b_4.txt")
int2 = np.loadtxt("tp1_1b_32.txt")
int3 = np.loadtxt("tp1_1b_128.txt")
probabilidades = np.loadtxt("vector_probabilidades.txt")

plt.figure(figsize=(6,7))

ax = plt.subplot(311)
ax.set_title("L=4")
ax.plot(probabilidades,int1)

ax = plt.subplot(312)
ax.set_title("L=32")
ax.plot(probabilidades,int2)

ax = plt.subplot(313)
ax.set_title("L=128")
ax.plot(probabilidades,int3)
plt.xlabel("p")
plt.ylabel("f(p)")

plt.tight_layout()