
import matplotlib.pyplot as plt

x = [1,5,10,15,20]
#avg Waiting times
rwavgreader=[0.82865,6.81711,19.0239,4.95613,12.6447]
rwavgwriter=[4.1384,27.1301,34.766,20.6807,37.5487]
frwavgreader=[1.35571,32.5551,15.5421,33.5389,49.0978]
frwavgwriter=[1.4376,31.4922,16.4189,35.3654,48.4327]


plt.xlabel("Number of Writer Threads")
plt.ylabel("Average Waiting Times(Milliseconds)")
plt.title("Average Waiting Time Vs Number of Writer Threads")
plt.plot(x,rwavgreader,marker = 'o',color = 'goldenrod',label = 'RW Reader')
plt.plot(x,rwavgwriter,marker = 'o',c='deepskyblue',label = 'RW Writer')
plt.plot(x,frwavgreader,marker = 'o',c='darkblue',label = 'FRW Reader')
plt.plot(x,frwavgwriter,marker = 'o',c='red',label = 'FRW Writer')
plt.legend()
plt.show()
