// Including Headers
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <fstream>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <chrono>
#include <random>

using namespace std;
ofstream output;
// this is the lock
std::atomic_bool l = false;
vector<bool> waiting;
// these are the waiting times
double maxwaiting = 0;
double avgwaiting = 0;
// This is the function of critical section
void testCS(int n, int k, int l1, int l2, int id)
{
    // these are the times to wait
    double t1, t2;
    for (int cnt = 0; cnt < k; ++cnt)
    {
        // this is the vector
        waiting[id] = true;
        bool key = true;
        // getting entertime
        time_t now = time(0);
        string reqEntertime = ctime(&now);
        auto start = std::chrono::steady_clock::now();
        reqEntertime[reqEntertime.size() - 1] = ' ';
        bool a = false;
        // while loop where the process waits until it executes it's critical section
        while (waiting[id] && key)
        {
            if (!atomic_compare_exchange_strong(&l, &a, true))
            {
                a = false;
            }
            else
            {
                key = false;
            }
        }
        // After it crosses, waiting[id] is false again
        waiting[id] = false;
        // Getting the time when it enters the critical section
        time_t now1 = time(0);
        string actEntertime = ctime(&now1);
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
        actEntertime[actEntertime.size() - 1] = ' ';
        // waitingtimes
        avgwaiting += elapsed.count();
        maxwaiting = max((double)elapsed.count(), maxwaiting);
        // Output
        output << cnt + 1 << "th CS Request at " << reqEntertime << "by thread " << id + 1 << endl;
        output << cnt + 1 << "th CS Entry at " << actEntertime << "by thread " << id + 1 << endl;
        // Generating random exponential distribution
        default_random_engine generator(time(NULL));
        exponential_distribution<double> d1(l1);
        exponential_distribution<double> d2(l2);
        t1 = d1(generator);
        t2 = d2(generator);
        // Critical section 
        sleep(t1);
        int j = (id + 1) % n;
        while ((j != id) && !waiting[j])
        {
            j = (j + 1) % n;
        }
        // After the critical section is completed
        now = time(0);
        string exitTime = ctime(&now);
        exitTime[exitTime.size() - 1] = ' ';
        // Output
        output << cnt + 1 << "th CS Exit at " << exitTime << "by thread " << id + 1 << endl;
        if (j == id)
        {
            l = false;
        }
        else
        {
            waiting[j] = false;
        }
        sleep(t2);
    }
}

int main()
{
    vector<std::thread> v;
    // These are the files to read and write
    ifstream file("inp-params.txt");
    output.open("output.txt");
    int n, k, l1, l2;
    file >> n >> k >> l1 >> l2;
    // Initialising the waiting array
    for (int i = 0; i < n; ++i)
    {
        waiting.push_back(false);
    }
    // Creating the n threads
    for (int i = 0; i < n; ++i)
    {
        v.emplace_back(testCS, n, k, l1, l2, i);
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