#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

// this is the point struct
struct Point
{
    int x, y;
};
typedef struct Point Point;

// This struct has all the data to send into the thread
struct ThreadAttr
{
    Point head;
    Point *points;
    int num_of_points_sent;
};
typedef struct ThreadAttr ThreadAttr;

// this converts a string of point into Point struct in a way we can use further
Point Convert(char *arr)
{
    Point temp;
    int i = 1;
    temp.x = 0;
    temp.y = 0;
    while (arr[i] != ',')
    {
        temp.x = temp.x * 10 + arr[i] - 48;
        i++;
    }
    i++;
    while (arr[i] != ')')
    {
        temp.y = temp.y * 10 + arr[i] - 48;
        i++;
    }
    return temp;
}

// This gives the Eucledian distance between 2 points
double EucledianDist(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// This is the thread function i.e, the function which we run in threads
void *thread_func(void *arg)
{
    ThreadAttr *attr = arg;
    Point head = attr[0].head;
    Point *points = attr[0].points;
    int num_of_points_sent = attr[0].num_of_points_sent;
    double minDist = EucledianDist(head, points[0]);
    int coord = 0;
    for (int i = 0; i < num_of_points_sent; i++)
    {
        if (EucledianDist(head, points[i]) < minDist)
        {
            minDist = EucledianDist(head, points[i]);
            coord = i;
        }
    }
    pthread_exit((void *)(points + coord));
}

int main(int argc, char *argv[])
{
    // num_of_threads denote the number of threads
    int num_of_threads;
    // This is the pointer to the input file
    FILE *file;
    // This opens the input file
    file = fopen("input.txt", "r");
    // This checks if the file is open or not
    if (file == NULL)
    {
        printf("File not opened properly\n");
        return 0;
    }
    // This takes input of num_of_threads
    fscanf(file, "%d", &num_of_threads);
    // this is the head point ot the main point
    Point head;
    // scanf("%d %d", &head.x, &head.y);
    char temp_t[50];
    // This takes the input point as a string
    fscanf(file, "%s", temp_t);
    // This converts the string into struct Point
    head = Convert(temp_t);
    // printf("(%d,%d)\n", head.x, head.y);
    // This denotes the num_of_points
    int num_of_points;
    // This takes input of the number of points
    fscanf(file, "%d", &num_of_points);
    // This is an array of number of points
    Point points[num_of_points];
    // This for loop takes input from the file as string and converts into Points and stores them in points array
    for (int i = 0; i < num_of_points; i++)
    {
        fscanf(file, "%s", temp_t);
        points[i] = Convert(temp_t);
    }
    // This closes the file because the input is taken
    fclose(file);
    // Creation of pthread_t 's
    pthread_t pid[num_of_threads];
    // These are the Thread attributes which we send to each thread
    ThreadAttr attr[num_of_threads];
    // This stores the values returned by the threads
    Point ThreadReturnPoints[num_of_threads];
    // int num_of_points_sent = num_of_points / num_of_threads;
    // This is the time part to find the time taken
    clock_t time;
    time = clock();
    int i = 0;
    for (int i = 0; i < num_of_threads; i++)
    {
        attr[i].num_of_points_sent = 0;
    }
    // This divides the number of points to send to each thread
    while (i < num_of_points)
    {
        attr[i % num_of_threads].num_of_points_sent++;
        i++;
    }
    int sum = 0;
    for (int i = 0; i < num_of_threads; i++)
    {
        // Here we are giving the attributes to send to the threads
        attr[i].head = head;
        // attr[i].num_of_points_sent = num_of_points_sent;
        // printf("%d ", attr[i].num_of_points_sent);
        attr[i].points = points + (sum);
        sum = sum + attr[i].num_of_points_sent;
        // Here, we create the threads and the threads run the function thread_func and the attributrs taken by them are attr[i]
        pthread_create(&pid[i], NULL, &thread_func, (void *)(attr + i));
        // void *temp;
        // //Temp takes the return value of the thread
        // pthread_join(pid[i], &temp);
        // // the value in temp is given to a temp_t point variable
        // Point *temp1 = (Point *)temp;
        // //This gives the return value of the thread to Thread return points array
        // ThreadReturnPoints[i] = (*temp1);
    }
    for (int i = 0; i < num_of_threads; i++)
    {
        void *temp;
        // Temp takes the return value of the thread
        pthread_join(pid[i], &temp);
        // the value in temp is given to a temp_t point variable
        Point *temp1 = (Point *)temp;
        // This gives the return value of the thread to Thread return points array
        ThreadReturnPoints[i] = (*temp1);
    }
    double min_dist = EucledianDist(head, ThreadReturnPoints[0]);
    int coord = 0;
    // This for loop chechks for the min distance from the points returned by the threads and stores the min distance in min_dist and the index in coord
    for (int i = 0; i < num_of_threads; i++)
    {
        if (EucledianDist(head, ThreadReturnPoints[i]) < min_dist)
        {
            min_dist = EucledianDist(head, ThreadReturnPoints[i]);
            coord = i;
        }
    }
    // Time checking
    time = clock() - time;
    // Changing time into double
    double time_t = ((double)(time)) / CLOCKS_PER_SEC;
    // Printing time
    printf("%lf microseconds\n", time_t * 1000000);
    // Printing the min dist point
    printf("(%d,%d)", ThreadReturnPoints[coord].x, ThreadReturnPoints[coord].y);
    return 0;
}