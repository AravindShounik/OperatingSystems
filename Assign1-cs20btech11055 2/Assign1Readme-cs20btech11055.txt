This code gives the point which is nearest to a given source in a set of points in a two-dimensional plane

This program is implemented using threads. 
Here, it takes an input of number of threads and the source and the set of points and then it divides the points in threads and finds the min distance of the set of points in each thread and then the threads return the point and then from the returned points, the main thread checks for the min_distance in the returned points of the threads.

To compile the following program, run the command 
```
gcc -o Assign1Src-cs20btech11055.c -lpthread -lm
```
To run the following program, run the command
```
./a.out
```

Here, before you run the program, the input is given to the code using a txt file named as input.txt the input should be in the format

num_of_threads
head point in the form (x,y)
num_of_points
all the points in the format (x,y)
