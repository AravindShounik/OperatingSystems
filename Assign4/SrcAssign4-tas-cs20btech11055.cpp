// Including Headers
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <fstream>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <random>

using namespace std;
ofstream output;
// Lock
std::atomic_flag l = ATOMIC_FLAG_INIT;
// Waiting times
double avgwaiting = 0;
double maxwaiting = 0;
// CS Function
void testCS(int k, int l1, int l2, int id)
{
    // Times to wait
    double t1, t2;
    for (int cnt = 0; cnt < k; ++cnt)
    {
        // Getting Entertime
        time_t now = time(0);
        string reqEntertime = ctime(&now);
        auto start = std::chrono::steady_clock::now();
        reqEntertime[reqEntertime.size() - 1] = ' ';
        // While loop where the process waits until it executes it's critical section
        while (l.test_and_set(std::memory_order_acquire))
            ;
        // Getting the time when it enters the critical section
        time_t now1 = time(0);
        string actEntertime = ctime(&now);
        actEntertime[actEntertime.size() - 1] = ' ';
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
        // waitingtimes
        avgwaiting = avgwaiting + difftime(now1, now);
        maxwaiting = max(difftime(now1, now), maxwaiting);
        // Output
        output << cnt + 1 << "th CS Request at " << reqEntertime << "by thread " << id + 1 << endl;
        output << cnt + 1 << "th CS Entry at " << actEntertime << "by thread " << id + 1 << endl;
        // Generating Random exponential distribution
        default_random_engine generator(time(NULL));
        exponential_distribution<double> d1(l1);
        exponential_distribution<double> d2(l2);
        t1 = d1(generator);
        t2 = d2(generator);
        // Critical section
        sleep(t1);
        // Time after the critical section is completed
        now = time(0);
        string exitTime = ctime(&now);
        exitTime[exitTime.size() - 1] = ' ';
        // Output
        output << cnt + 1 << "th CS Exit at " << exitTime << "by thread " << id + 1 << endl;
        l.clear(std::memory_order_release); // release lock
        sleep(t2);
    }
}

int main()
{
    vector<std::thread> v;
    // These are files to read and write
    ifstream file("inp-params.txt");
    output.open("output.txt");
    int n, k, l1, l2;
    file >> n >> k >> l1 >> l2;
    // Creating n threads
    for (int i = 0; i < n; ++i)
    {
        v.emplace_back(testCS, k, l1, l2, i);
    }
    // Joining the threads
    for (auto &t : v)
    {
        t.join();
    }
    avgwaiting = avgwaiting / (n * k);
    // cout << "Average Waiting Time = " << avgwaiting << endl;
    // cout << "Maximum Waiting Time = " << maxwaiting << endl;
    // Closing the files
    output.close();
    file.close();
}