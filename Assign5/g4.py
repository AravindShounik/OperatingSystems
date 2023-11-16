
import matplotlib.pyplot as plt

x = [1,5,10,15,20]
#avg Waiting times
rwavgreader=[15.914,86.882,160.628,86.538,107.998]
rwavgwriter=[40.236,163.071,243.635,184.567,238.121]
frwavgreader=[6.055,176.463,116.741,135.423,213.908]
frwavgwriter=[0.00268,0.148978,0.091941,0.125962,0.261265]


plt.xlabel("Number of Writer Threads")
plt.ylabel("Max Waiting Times(Milliseconds)")
plt.title("Max Waiting Time Vs Number of Writer Threads")
plt.plot(x,rwavgreader,marker = 'o',color = 'goldenrod',label = 'RW Reader')
plt.plot(x,rwavgwriter,marker = 'o',c='deepskyblue',label = 'RW Writer')
plt.plot(x,frwavgreader,marker = 'o',c='darkblue',label = 'FRW Reader')
plt.plot(x,frwavgwriter,marker = 'o',c='red',label = 'FRW Writer')
plt.legend()
plt.show()
