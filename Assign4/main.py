#Maximum Waiting Times

import matplotlib.pyplot as plt

x = [10,20,30,40,50]
#cas
ycas = [107,295,284,723,1235]
#tas
ytas = [95,236,249,685,1149]
#cas_bounded
ycas_b = [73,267,300,1000,1500]

plt.xlabel("Max Waiting Time")
plt.ylabel("Number of Threads")
plt.title("Max-Waiting Time Vs Number of Threads")
plt.plot(x,ycas,marker = 'o',color = 'green',label = 'CAS ME')
plt.plot(x,ycas_b,marker = 'o',c='red',label = 'CAS Bounded ME')
plt.plot(x,ytas,marker = 'o',c='blue',label = 'TAS ME')
plt.legend(loc = 'lower right')
plt.show()
