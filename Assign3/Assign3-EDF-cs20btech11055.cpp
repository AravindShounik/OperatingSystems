#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

fstream file;
// This is the struct which contains the data of a process
struct Process
{
    int pid;       // process id
    int t;         // time taken to execute
    int p;         // period
    int k;         // number of such processes
    int remaining; // remaining time for the process to complete execution
    int deadline;  // the deadline in which the process should finfish execution
};
// this function checks which process has the id which we are looking for
int check(vector<Process> process, int n, int pid)
{
    for (int i = 0; i < n; i++)
    {
        if (process[i].pid == pid)
        {
            return i;
        }
    }
    return -1;
}

int t = 0;

void EDFscheduling()
{
    // the variable terminated holds the number of processes terminated
    int terminated = 0;
    // edflogfile has the file in which logs are stored
    ofstream edflogfile("EDF-Log.txt");
    // edfstatsfile has the file in which stats are stored
    ofstream edfstatsfile("EDF-Stats.txt");
    // this vector stores all the processes
    vector<Process> process;
    Process a;
    // total is the total number of processes present
    int n, total = 0;
    // n id the total number of distinct processes present
    file >> n;
    // k[n] contains the number of processes of each process
    int k[n];
    // Waitingtime[n] contains total waiting time for a process
    double waitingtime[n];
    // This is the comparator for the min heap created below
    // it checks their deadline and if their deadline is same, it checks remaining
    auto cmp = [](Process left, Process right)
    { if(left.deadline!=right.deadline){return (left.deadline) >= (right.deadline);}
  else{return left.remaining>=right.remaining;} };
    // This is the waiting queue of the processes, here, if a process enters, the process reaches  it's place directly because it's a priority queue
    priority_queue<Process, vector<Process>, decltype(cmp)> WaitingQueue(cmp);
    for (int i = 0; i < n; i++)
    {
        // this takes the inputs from the file
        file >> a.pid >> a.t >> a.p >> a.k;
        a.remaining = a.t;
        a.deadline = a.p;
        total += a.k;
        k[i] = a.k;
        waitingtime[i] = 0;
        process.push_back(a);
        WaitingQueue.push(a);
        // printing logs
        edflogfile << "Process P" << a.pid << " processing time: " << a.t << " deadline: " << a.p << " period: " << a.p << " joined the system at time t = " << t << endl;
    }
    Process exec = WaitingQueue.top();
    // initially first process starts executing
    edflogfile << "Process P" << exec.pid << " starts executing at time t = " << t << endl;
    int completed = 0;
    // this while loop runs until the completed process are equal to total processes
    while (completed < total)
    {
        // initially t is updated
        t++;
        // this has 3 cases
        // Case 1: Waiting Queue is empty,
        //  In this case, the a process can be added to th queue because new processes come periodically in this stimulation

        if (WaitingQueue.empty())
        {
            // adding the new processes which came to the system at this instant
            for (int i = 0; i < n; i++)
            {
                if (t % process[i].p == 0 && process[i].k > 1)
                {
                    process[i].k--;
                    process[i].deadline = t + process[i].p;
                    a = process[i];
                    WaitingQueue.push(a);
                }
            }
            // if the waiting queue is not empty after the processes are added the first process executes
            if (!WaitingQueue.empty())
            {
                edflogfile << "CPU is idle till time t = " << t << endl;
                edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
            }
        }

        // Case 2: if a process completes execution at this instant
        else if (WaitingQueue.top().remaining == 1)
        {
            edflogfile << "Process P" << WaitingQueue.top().pid << " is completed at time t = " << t << endl;
            waitingtime[check(process, n, WaitingQueue.top().pid)] += t - WaitingQueue.top().t - WaitingQueue.top().deadline + WaitingQueue.top().p;

            WaitingQueue.pop();
            completed++;
            queue<Process> tempQueue;
            // we check for any terminated processes and remove them
            while (!WaitingQueue.empty())
            {
                if (WaitingQueue.top().deadline > t)
                {
                    // edflogfile << WaitingQueue.top().pid << " is pushed to tempQueue" << endl;
                    tempQueue.push(WaitingQueue.top());
                    WaitingQueue.pop();
                }
                else
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " is terminated because it reaches it's deadline at time t = " << t << endl;
                    waitingtime[check(process, n, WaitingQueue.top().pid)] += WaitingQueue.top().p - WaitingQueue.top().t + WaitingQueue.top().remaining;
                    terminated++;
                    WaitingQueue.pop();
                    completed++;
                }
            }
            while (!tempQueue.empty())
            {
                // edflogfile << WaitingQueue.top().pid << " is pushed to WaitingQueue" << endl;
                WaitingQueue.push(tempQueue.front());
                tempQueue.pop();
            }
            // adding the new processes which came to the system at this instant
            for (int i = 0; i < n; i++)
            {
                if (t % process[i].p == 0 && process[i].k > 1)
                {
                    process[i].k--;
                    process[i].deadline = t + process[i].p;
                    a = process[i];
                    WaitingQueue.push(a);
                }
            }
            // Then it starts the top process
            if (!WaitingQueue.empty())
            {
                if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                }
                else
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                }
            }
        }
        // Case 3 : any other condition
        // It can happen that any process can preempt it
        // The running process can be terminated because it's deadline has reached
        else
        {
            Process exec = WaitingQueue.top();
            exec.remaining--;
            WaitingQueue.pop();
            WaitingQueue.push(exec);
            bool inwhile = false;

            queue<Process> tempQueue;
            bool istopterminated = false;
            if (WaitingQueue.top().deadline <= t)
            {
                istopterminated = true;
            }
            while (!WaitingQueue.empty())
            {
                if (WaitingQueue.top().deadline > t)
                {
                    // edflogfile << WaitingQueue.top().pid << " is pushed to tempQueue" << endl;
                    tempQueue.push(WaitingQueue.top());
                    WaitingQueue.pop();
                }
                else
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " is terminated because it's deadline is at time t = " << t << endl;
                    waitingtime[check(process, n, WaitingQueue.top().pid)] += WaitingQueue.top().p - WaitingQueue.top().t + WaitingQueue.top().remaining;
                    terminated++;
                    WaitingQueue.pop();
                    completed++;
                }
            }
            while (!tempQueue.empty())
            {
                // edflogfile << WaitingQueue.top().pid << " is pushed to WaitingQueue" << endl;
                WaitingQueue.push(tempQueue.front());
                tempQueue.pop();
            }
            // adding the new processes
            for (int i = 0; i < n; i++)
            {
                if (t % process[i].p == 0 && process[i].k > 1)
                {
                    process[i].k--;
                    a = process[i];
                    a.deadline = process[i].p + t;
                    WaitingQueue.push(a);
                }
            }
            if (istopterminated)
            {
                if (!WaitingQueue.empty())
                {
                    if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                    {
                        edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                    }
                    else
                    {
                        edflogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                    }
                }
            }
            else if (WaitingQueue.top().pid != exec.pid)
            {
                edflogfile << "Process P" << exec.pid << " is preempted by Process P" << WaitingQueue.top().pid << " at time t = " << t << " remaining time t = " << exec.remaining << endl;
                if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                }
                else
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                }
            }
        }
    }
    // cout << terminated << endl;
    edflogfile.close();
    // this checks the total waiting time of a process
    double totalwaitingtime = 0;
    edfstatsfile << "Number of processes that came into the system = " << total << endl;
    edfstatsfile << "Number of processes that are successfully completed = " << total - terminated << endl;
    edfstatsfile << "Number of processes terminated = " << terminated << endl;
    for (int i = 0; i < n; i++)
    {
        edfstatsfile << "The waiting time of Process P" << process[i].pid << " is " << waitingtime[i] / k[i] << endl;
        totalwaitingtime += waitingtime[i];
    }
    edfstatsfile << "Total waiting time is " << totalwaitingtime / total << endl;
    edfstatsfile.close();
}

int main()
{
    file.open("inp-params.txt");
    EDFscheduling();
    file.close();
}