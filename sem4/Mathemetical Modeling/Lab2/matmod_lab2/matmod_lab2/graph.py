import matplotlib.pyplot as plt
import numpy as np
import sys

m = np.loadtxt(sys.argv[1])
plt.title(sys.argv[1])
plt.subplot (2, 1, 1)
plt.hist(m, 5)
plt.title ("histogram")

plt.subplot (2, 1, 2)
plt.scatter(np.arange(0, len(m), 1), m, 0.5, 'r')
plt.title ("distribution")

plt.show()