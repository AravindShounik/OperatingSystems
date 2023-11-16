import numpy as np

x = np.random.randint(2000, size=(5000,2))
head = np.random.randint(2000,size=(1,2))
num_of_Threads = np.random.randint(1,200)

f= open("input.txt","w+")

f.write("%d\n"%num_of_Threads)
f.write("(%d"%head[0][0])
f.write(',%d)\n'%head[0][1])
f.write("5000\n")


for i in range(5000):
    f.write("(%d"%x[i][0])
    f.write(',%d)\n'%x[i][1])