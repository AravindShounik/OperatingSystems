// Including Headers
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <atomic>
#include <fstream>
#include <vector>
#include <thread>
#include <ctime>
#include <unistd.h>
#include <random>
#define K 2

using namespace std;
// Flags and Semaphores and atomic integers
atomic_flag l = ATOMIC_FLAG_INIT; // This flag is for input output statements If we don't use this flag, the output statements are overlapping
sem_t mutex_t;                    // This is to check whether atleast one reader is there in the room.
sem_t subject_t;                  // This is to check whether anyone is inside the room or not.
atomic_int readcount(0);          // this keeps count of the number of readers in the room
atomic_int subject(0);            // This is to know which subject is being read in the room
// Files
ifstream input("input-a.txt");                   // This is the input file.
ofstream output("LogFile-cs20btech11055-A.txt"); // This is the output file.
// Waiting times
double WaitingTime = 0;
double MaxWaitingTime = 0;
//  When a student comes, we call this function.
void Student(int m, int n, int i, int mu)
{
    time_t now;
    // This is to know which subject he is reading which is taken randomly.
    int ran = rand() % K; // Note that K=2 in this case
    ran = ran + 1;        // This is to make sure the number is either 1 or 2
    now = time(0);
    string reqTime = ctime(&now);
    reqTime[reqTime.size() - 1] = ' ';
    while (l.test_and_set(std::memory_order_acquire))
        ;
    clock_t start = clock();
    output << "Student" << i << " group k" << ran << " Requested the lab at " << reqTime << endl;
    l.clear(std::memory_order_release);
    // This checks whether the subject is either the subject the student wants to read or there are no people in the room at all and breaks the loop only when either the subject is same or no person is in the room
    while (subject != ran && subject != 0)
        ;
    sem_wait(&mutex_t);
    // This breaks only when there are less than m people in the room
    while (readcount >= m)
        ;
    readcount++;
    now = time(0);
    string EnterTime = ctime(&now);
    EnterTime[EnterTime.size() - 1] = ' ';
    while (l.test_and_set(std::memory_order_acquire))
        ;
    clock_t end = clock();
    double time_used = ((double)end - start) / CLOCKS_PER_SEC;
    WaitingTime += time_used;
    MaxWaitingTime = max(MaxWaitingTime, time_used);
    output << "Student" << i << " group k" << ran << " Entered the lab at " << EnterTime << endl;
    l.clear(std::memory_order_release);
    if (readcount == 1)
    {
        sem_wait(&subject_t);
        subject = ran;
    }
    sem_post(&mutex_t);
    default_random_engine generator(time(NULL));
    exponential_distribution<double> d(mu);
    double t = d(generator);
    // reading time
    sleep(t);
    sem_wait(&mutex_t);
    now = time(0);
    string ExitTime = ctime(&now);
    ExitTime[ExitTime.size() - 1] = ' ';
    while (l.test_and_set(std::memory_order_acquire))
        ;
    output << "Student" << i << " group k" << ran << " Exited the lab at " << ExitTime << endl;
    l.clear(std::memory_order_release);
    readcount--;
    // If there are no readers, then subject_t is released and subject is also set to 0, i.e, no subject
    if (readcount == 0)
    {
        sem_post(&subject_t);
        subject = 0;
    }
}

int main()
{
    // Initialising Semaphores
    sem_init(&mutex_t, 0, 1);
    sem_init(&subject_t, 0, 1);
    int k, m, l, n, mu;
    // Taking input from file
    input >> m >> l >> n >> mu;
    // cout << "m " << m << endl;
    default_random_engine generator(time(NULL));
    exponential_distribution<double> d(l);
    std::vector<std::thread> v;
    for (int i = 0; i < n; i++)
    {
        v.emplace_back(Student, m, n, i + 1, mu);
        double t = d(generator);
        // There is a gap between each student and it is the sleep time which is generated using random_generator using exponential distribution
        sleep(t);
    }
    // Joining the threads back
    for (auto &t : v)
    {
        t.join();
    }

    // Waiting Times

    WaitingTime = WaitingTime / n;
    cout << "Average Waiting Time = " << WaitingTime * 1000 << "ms" << endl;
    cout << "Maximum Waiting Time = " << MaxWaitingTime * 1000 << "ms" << endl;

    // Closing the files.
    input.close();
    output.close();
}

// Here, we can see that the program works for every k and it even allows multiple readers reading the same subject into the hall but the max number of readers allowed is m