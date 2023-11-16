import matplotlib.pyplot as plt
import numpy as np

xpoints = [1000,1401,3000,4000,5000]
# ysequential = [1539,1756,1915,1543,1782]
# ysequential = [1297,1553,1704,2646,2541]
yparallel = [1024,1540,1830,2184,2189]
# yparallel = [1144,1238,1319,1493,1669]
# yparallel = [1044,1540,1566,1569,1762]
ysequential = [1005,1350,1640,1764,1769]

plt.xlabel("Number of Points")
plt.ylabel("Time Taken (in microseconds)")
plt.text(1000,2100,"Number of threads = 16")
plt.title("Number of points vs Time Taken")
plt.plot(xpoints,ysequential,marker = "o",c = "red",label = "Sequential")
plt.plot(xpoints,yparallel,marker = "o",c = "green",label = "Parallel")
plt.legend(loc = "lower right")
plt.show()