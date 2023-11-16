
import matplotlib.pyplot as plt
import numpy as np

xpoints = [1,2,4,8,16]
yparallel = [621,1120,1282,1747,1900]
# yparallel = [740,811,986,1235,1662]
# ysequential = [493,912,979,1359,1780]
ysequential = [745,652,1076,1402,1630]

plt.text(1,1850,"Number of Points = 5000")
plt.xticks(np.arange(1,17))
plt.xlabel("Number of Threads")
plt.ylabel("Time taken(in MicroSeconds)")
plt.title("Number of threads vs Time taken")
plt.plot(xpoints,ysequential,marker = "o", c = "red",label = "Sequential")
plt.plot(xpoints,yparallel,marker = "o", c = "green",label = "Parallel")
plt.legend(loc = "lower right")

plt.show()