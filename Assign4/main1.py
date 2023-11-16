# Avg Waiting Times

import matplotlib.pyplot as plt

x = [10,20,30,40,50]
#cas
ycas = [7.27,28.595,134.2633,242.3225,295.846]
#tas
ytas = [7,37.5,92.3333,181.25,263.2]
#cas_bounded
ycas_b = [34.84,353.57,611.44,594.878,992.742]

plt.xlabel("Number of Threads")
plt.ylabel("Avg Waiting Time")
plt.title("Number of Threads Vs Average Waiting Time")
plt.plot(x,ycas,marker = 'o',color = 'green',label = 'CAS ME')
plt.plot(x,ycas_b,marker = 'o',c='red',label = 'CAS Bounded ME')
plt.plot(x,ytas,marker = 'o',c='blue',label = 'TAS ME')
plt.legend(loc = 'lower right')
plt.show()
