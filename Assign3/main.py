import matplotlib.pyplot as plt

x = [20,30,40,50,60,70,80,90,100]
#edf
yrms = [0,12,18,27,37,45,51,62,72]
#rms
yedf = [0,13,18,37,47,56,65,74,84]

plt.xlabel("Number of Processes")
plt.ylabel("Number of Deadlines Missed")
plt.title("Number of Processes Vs Number of Deadlines Missed")
plt.plot(x,yrms,marker = 'o',color = 'green',label = 'RMS Scheduling')
plt.plot(x,yedf,marker = 'o',c='red',label = 'EDF Scheduling')
plt.legend(loc = 'lower right')
plt.show()
