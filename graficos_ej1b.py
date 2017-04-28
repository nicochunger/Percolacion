# Graficos del ejercicio 1b de la practica de Percolacion

import numpy as np
import matplotlib.pyplot as plt

p_c = []
p_c.append(0.561233)
p_c.append(0.578518)
p_c.append(0.587189)
p_c.append(0.593840)
p_c.append(0.592510)
p_c.append(0.592605)

disp = []
disp.append(0.102822)
disp.append(0.070637)
disp.append(0.045259)
disp.append(0.027699)
disp.append(0.016983)
disp.append(0.009656)

plt.plot(disp,p_c)

ajuste = np.polyfit(disp,p_c,1)
x_fit = np.linspace(disp[0],disp[-1],100)
y_fit = ajuste[1] + ajuste[0]*x_fit

plt.plot(x_fit,y_fit,"r")
plt.show()

print ajuste