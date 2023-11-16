
import matplotlib.pyplot as plt

x = [1,5,10,15,20]
#avg Waiting times
rwavgreader=[13.309,11.556,86.739,173.763,463.198]
rwavgwriter=[13.116,77.301,208.777,556.587,1220.82]
frwavgreader=[16.415,43.51,111.742,207.382,322.464]
frwavgwriter=[0.021062,0.0432,0.119486,0.171807,0.274475]


plt.xlabel("Number of Reader Threads")
plt.ylabel("Max Waiting Times(Milliseconds)")
plt.title("Max Waiting Time Vs Number of Reader Threads")
plt.plot(x,rwavgreader,marker = 'o',color = 'goldenrod',label = 'RW Reader')
plt.plot(x,rwavgwriter,marker = 'o',c='deepskyblue',label = 'RW Writer')
plt.plot(x,frwavgreader,marker = 'o',c='darkblue',label = 'FRW Reader')
plt.plot(x,frwavgwriter,marker = 'o',c='red',label = 'FRW Writer')
plt.legend()
plt.show()
