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
using namespace std;
// Flags and semaphores
std::atomic_flag l = ATOMIC_FLAG_INIT;
sem_t resource;
sem_t r_mutex;
sem_t servicequeue;
std::atomic_int readcount(0);
std::atomic_int writecount(0);
// Waiting times
double readerwaitingtime = 0;
double writerwaitingtime = 0;
double maxreader = 0;
double maxwriter = 0;
// Files
std::ifstream input("inp-params.txt");
std::ofstream output("FRW-log.txt");
// Reaader Function
void Reader(int kr, int id, int l1, int l2)
{
    time_t now;
    double t1, t2;
    for (int i = 0; i < kr; i++)
    {
        now = time(0);
        string reqTime = ctime(&now);
        reqTime[reqTime.size() - 1] = ' ';
        while (l.test_and_set(std::memory_order_acquire))
            ;
        clock_t start = clock();
        output << i + 1 << "th CS Request at " << reqTime << "by Reader thread " << id + 1 << endl;
        l.clear(std::memory_order_release);

        sem_wait(&servicequeue);
        sem_wait(&r_mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&resource);
        sem_post(&servicequeue);
        sem_post(&r_mutex);

        now = time(0);
        string Entertime = ctime(&now);
        Entertime[Entertime.size() - 1] = ' ';
        while (l.test_and_set(std::memory_order_acquire))
            ;
        clock_t end = clock();
        double time_used = ((double)end - start) / CLOCKS_PER_SEC;
        maxreader = max(maxreader, time_used);
        readerwaitingtime += time_used;
        output << i + 1 << "th CS Entry at " << reqTime << "by Reader thread " << id + 1 << endl;
        l.clear(std::memory_order_release);
        default_random_engine generator(time(NULL));
        exponential_distribution<double> d1(l1);
        exponential_distribution<double> d2(l2);
        t1 = d1(generator);
        t2 = d2(generator);
        sleep(t1);

        sem_wait(&r_mutex);
        readcount--;
        if (readcount == 0)
        {
            sem_post(&resource);
        }
        sem_post(&r_mutex);

        now = time(0);
        string exittime = ctime(&now);
        exittime[exittime.size() - 1] = ' ';
        while (l.test_and_set(std::memory_order_acquire))
            ;
        output << i + 1 << "th CS Exit at " << reqTime << "by Reader thread " << id + 1 << endl;
        l.clear(std::memory_order_release);
        sleep(t2);
    }
}
// Writer Function
void Writer(int kw, int id, int l1, int l2)
{
    time_t now;
    for (int i = 0; i < kw; i++)
    {
        now = time(0);
        double t1, t2;
        string reqTime = ctime(&now);
        reqTime[reqTime.size() - 1] = ' ';
        while (l.test_and_set(std::memory_order_acquire))
            ;
        clock_t start = clock();
        output << i + 1 << "th CS Request at " << reqTime << "by Writer thread " << id + 1 << endl;
        l.clear(std::memory_order_release);

        sem_wait(&servicequeue);
        sem_wait(&resource);
        sem_post(&servicequeue);
        writecount++;

        while (l.test_and_set(std::memory_order_acquire))
            ;
        clock_t end = clock();
        double time_used = ((double)end - start) / CLOCKS_PER_SEC;
        maxwriter = max(maxwriter, time_used);
        writerwaitingtime += time_used;
        output << i + 1 << "th CS Entry at " << reqTime << "by Writer thread " << id + 1 << endl;
        l.clear(std::memory_order_release);
        default_random_engine generator(time(NULL));
        exponential_distribution<double> d1(l1);
        exponential_distribution<double> d2(l2);
        t1 = d1(generator);
        t2 = d2(generator);
        sleep(t1);
        sem_post(&resource);
        writecount--;
        now = time(0);
        string exittime = ctime(&now);
        exittime[exittime.size() - 1] = ' ';
        while (l.test_and_set(std::memory_order_acquire))
            ;
        output << i + 1 << "th CS Exit at " << reqTime << "by Writer thread " << id + 1 << endl;
        l.clear(std::memory_order_release);
        sleep(t2);
    }
}
// Main
int main()
{
    sem_init(&resource, 0, 1);
    sem_init(&r_mutex, 0, 1);
    sem_init(&servicequeue, 0, 1);
    int nw, nr, kw, kr, l1, l2;
    input >> nw >> nr >> kw >> kr >> l1 >> l2;
    std::vector<std::thread> v;
    for (int i = 0; i < nr; i++)
    {
        v.emplace_back(Reader, kr, i, l1, l2);
    }
    for (int i = 0; i < nw; i++)
    {
        v.emplace_back(Writer, kw, i, l1, l2);
    }
    for (auto &t : v)
    {
        t.join();
    }
    readerwaitingtime = readerwaitingtime / (nr * kr);
    writerwaitingtime = writerwaitingtime / (nw * kw);
    ofstream text("Average_time_frw.txt");
    text << "Average Waiting time of reader in milliseconds is " << readerwaitingtime * 1000 << endl;
    text << "Average Waiting time of writer in milliseconds is " << writerwaitingtime * 1000 << endl;
    text << "Maximum Waiting time of reader in milliseconds is " << maxreader * 1000 << endl;
    text << "Maximum Waiting time of writer in milliseconds is " << maxwriter << endl;
    input.close();
    output.close();
    text.close();
}