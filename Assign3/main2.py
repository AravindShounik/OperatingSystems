import matplotlib.pyplot as plt

x = [20,30,40,50,60,70,80,90,100]
#edf
yrms = [6,26.6667,29.25,36.1,40.1667,39.4286,42.8125,45.5,50]
#rms
yedf = [6,31.6667,33.875,41.7,44.75,42.9286,46.375,48.4444,52.9]

plt.xlabel("Number of Processes")
plt.ylabel("Average Waiting Time")
plt.title("Number of Processes Vs Average Waiting Time")

plt.plot(x,yrms,marker = 'o',color = 'green',label = 'RM Scheduling')
plt.plot(x,yedf,marker = 'o',c='red',label = 'EDF Scheduling')
plt.legend(loc = 'lower right')
plt.show()
