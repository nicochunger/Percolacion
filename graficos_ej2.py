# Programa que hace los graficos para el ejercicio 2 de la guia 1 de percolacion

import numpy as np
import matplotlib.pyplot as plt

# Imoprta los datos
intensidades = np.loadtxt("tp1_2_4.txt")
probabilidades = np.loadtxt("vector_probabilidades.txt")

plt.plot(probabilidades,intensidades)
