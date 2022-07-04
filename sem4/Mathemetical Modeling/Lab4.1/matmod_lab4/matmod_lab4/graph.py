import matplotlib.pyplot as plt
import numpy as np
import sys


X = np.loadtxt('X.txt')
Y = np.loadtxt('Y.txt')

V = [];

for i in X:
	V.append(float(sys.argv[1]))

plt.plot(X, Y, 'r',
		 X, V, 'b--')

plt.xlabel('N')
plt.ylabel('E')
plt.title('Integrall')
plt.legend(['Calculated\nvalues',
            'Real value'],
            loc='lower right')

plt.show()