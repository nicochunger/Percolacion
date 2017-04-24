# Graficos del ejercicio 6 de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

m2 = np.loadtxt("tp1_6_m2.txt")
p = np.loadtxt("tp1_6_probas.txt")

dx = np.diff(p)
dy = np.diff(m2)
D = dy/dx

plt.plot(p,m2,".")
