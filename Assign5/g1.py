
import matplotlib.pyplot as plt

x = [1,5,10,15,20]
#avg Waiting times
rwavgreader=[2.7321,1.58932,8.03526,14.6954,31.3726]
rwavgwriter=[2.52059,8.17331,27.1918,67.116,101.004]
frwavgreader=[4.2496,6.21624,27.373,42.457,31.0001]
frwavgwriter=[3.51866,7.10287,28.0878,39.1925,42.8231]


plt.xlabel("Number of Reader Threads")
plt.ylabel("Average Waiting Times(Milliseconds)")
plt.title("Average Waiting Time Vs Number of Reader Threads")
plt.plot(x,rwavgreader,marker = 'o',color = 'goldenrod',label = 'RW Reader')
plt.plot(x,rwavgwriter,marker = 'o',c='deepskyblue',label = 'RW Writer')
plt.plot(x,frwavgreader,marker = 'o',c='darkblue',label = 'FRW Reader')
plt.plot(x,frwavgwriter,marker = 'o',c='red',label = 'FRW Writer')
plt.legend()
plt.show()
