#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

fstream file;

struct Process
{
    int pid;
    int t, p, k;
    int remaining, deadline;
};

int t = 0;
void RMscheduling()
{
    int terminated = 0;
    ofstream rmlogfile("RM-Log.txt");
    vector<Process> process;
    Process a;
    int n, total = 0;
    file >> n;
    auto cmp = [](Process left, Process right)
    { if(left.pid!=right.pid){return (left.p) >= (right.p);}
    else{return left.remaining>=right.remaining;} };
    priority_queue<Process, vector<Process>, decltype(cmp)> WaitingQueue(cmp);
    for (int i = 0; i < n; i++)
    {
        file >> a.pid >> a.t >> a.p >> a.k;
        a.remaining = a.t;
        a.deadline = a.p;
        total += a.k;
        process.push_back(a);
        WaitingQueue.push(a);
        rmlogfile << "Process P" << a.pid << " processing time: " << a.t << " deadline: " << a.p << " period: " << a.p << " joined the system at time t = " << t << endl;
    }
    Process exec = WaitingQueue.top();
    rmlogfile << "Process P" << exec.pid << " starts executing at time t = " << t << endl;
    int completed = 0;

    while (completed < total)
    {
        t++;
        if (WaitingQueue.empty())
        {
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
            if (!WaitingQueue.empty())
            {
                rmlogfile << "CPU is idle till time t = " << t - 1 << endl;
                rmlogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t << endl;
            }
        }
        else if (WaitingQueue.top().remaining == 1)
        {
            rmlogfile << "Process P" << WaitingQueue.top().pid << " is completed at time t = " << t << endl;
            WaitingQueue.pop();
            completed++;
            while (!WaitingQueue.empty() && WaitingQueue.top().deadline <= t)
            {
                rmlogfile << "Process P" << WaitingQueue.top().pid << " is terminated because it's deadline is at time t = " << WaitingQueue.top().deadline << endl;
                terminated++;
                WaitingQueue.pop();
                completed++;
            }
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

            if (!WaitingQueue.empty())
            {
                if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                {
                    rmlogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                }
                else
                {
                    rmlogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                }
            }
        }
        else
        {
            Process exec = WaitingQueue.top();
            exec.remaining--;
            WaitingQueue.pop();
            WaitingQueue.push(exec);
            bool inwhile = false;
            while (!WaitingQueue.empty() && WaitingQueue.top().deadline <= t)
            {
                inwhile = true;
                rmlogfile << "Process P" << WaitingQueue.top().pid << " is terminated because it's deadline is at time t = " << WaitingQueue.top().deadline << endl;
                terminated++;
                WaitingQueue.pop();
                completed++;
            }
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
            if (inwhile)
            {
                if (!WaitingQueue.empty())
                {
                    if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                    {
                        rmlogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                    }
                    else
                    {
                        rmlogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                    }
                }
            }
            else if (WaitingQueue.top().pid != exec.pid)
            {
                rmlogfile << "Process P" << exec.pid << " is preempted by Process P" << WaitingQueue.top().pid << " at time t = " << t << " remaining time t = " << exec.remaining << endl;
                if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                {
                    rmlogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                }
                else
                {
                    rmlogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                }
            }
        }
    }
    cout << terminated << endl;
    rmlogfile.close();
}

void EDFscheduling()
{
    int terminated = 0;
    ofstream edflogfile("EDF-Log.txt");
    vector<Process> process;
    Process a;
    int n, total = 0;
    file >> n;
    int arr[n], waitingtime[n], starttime[n];
    auto cmp = [](Process left, Process right)
    { if(left.deadline!=right.deadline){return (left.deadline) >= (right.deadline);}
  else{return left.remaining>=right.remaining;} };
    priority_queue<Process, vector<Process>, decltype(cmp)> WaitingQueue(cmp);
    for (int i = 0; i < n; i++)
    {
        file >> a.pid >> a.t >> a.p >> a.k;
        a.remaining = a.t;
        a.deadline = a.p;
        total += a.k;
        arr[i] = a.k;
        waitingtime[i] = 0;
        starttime[i] = 0;
        process.push_back(a);
        WaitingQueue.push(a);
        edflogfile << "Process P" << a.pid << " processing time: " << a.t << " deadline: " << a.p << " period: " << a.p << " joined the system at time t = " << t << endl;
    }
    Process exec = WaitingQueue.top();
    edflogfile << "Process P" << exec.pid << " starts executing at time t = " << t << endl;
    int completed = 0;

    while (completed < total)
    {
        t++;
        if (WaitingQueue.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (t % process[i].p == 0 && process[i].k > 1)
                {
                    process[i].k--;
                    process[i].deadline = t + process[i].p;
                    a = process[i];
                    WaitingQueue.push(a);
                    waitingtime[i] += t;
                }
            }
            if (!WaitingQueue.empty())
            {
                edflogfile << "CPU is idle till time t = " << t - 1 << endl;
                edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t << endl;
            }
        }
        else if (WaitingQueue.top().remaining == 1)
        {
            edflogfile << "Process P" << WaitingQueue.top().pid << " is completed at time t = " << t << endl;
            WaitingQueue.pop();
            completed++;
            while (!WaitingQueue.empty() && WaitingQueue.top().deadline <= t)
            {
                edflogfile << "Process P" << WaitingQueue.top().pid << " is terminated because it's deadline is at time t = " << WaitingQueue.top().deadline << endl;
                terminated++;
                WaitingQueue.pop();
                completed++;
            }
            for (int i = 0; i < n; i++)
            {
                if (t % process[i].p == 0 && process[i].k > 1)
                {
                    process[i].k--;
                    process[i].deadline = t + process[i].p;
                    a = process[i];
                    WaitingQueue.push(a);
                    waitingtime[i] += t;
                }
            }

            if (!WaitingQueue.empty())
            {
                if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                    starttime[WaitingQueue.top().pid - 1] += (t + 1);
                }
                else
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                }
            }
        }
        else
        {
            Process exec = WaitingQueue.top();
            exec.remaining--;
            WaitingQueue.pop();
            WaitingQueue.push(exec);
            bool inwhile = false;
            while (!WaitingQueue.empty() && WaitingQueue.top().deadline <= t)
            {
                inwhile = true;
                edflogfile << "Process P" << WaitingQueue.top().pid << " is terminated because it's deadline is at time t = " << WaitingQueue.top().deadline << endl;
                terminated++;
                WaitingQueue.pop();
                completed++;
            }
            for (int i = 0; i < n; i++)
            {
                if (t % process[i].p == 0 && process[i].k > 1)
                {
                    process[i].k--;
                    a = process[i];
                    a.deadline = process[i].p + t;
                    WaitingQueue.push(a);
                    waitingtime[a.pid - 1] += t;
                }
            }
            if (inwhile)
            {
                if (!WaitingQueue.empty())
                {
                    if (WaitingQueue.top().remaining == WaitingQueue.top().t)
                    {
                        edflogfile << "Process P" << WaitingQueue.top().pid << " starts executing at time t = " << t + 1 << endl;
                        starttime[WaitingQueue.top().pid - 1] += (t + 1);
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
                    starttime[WaitingQueue.top().pid - 1] += (t + 1);
                }
                else
                {
                    edflogfile << "Process P" << WaitingQueue.top().pid << " resumed executing at time t = " << t + 1 << endl;
                }
            }
        }
    }
    cout << terminated << endl;
    edflogfile.close();
    ofstream edfstatsfile("EDF-Stats.txt");
    edfstatsfile << "Number of processes that came into the system = " << total << endl;
    edfstatsfile << "Number of processes that are successfully completed = " << total - terminated << endl;
    edfstatsfile << "Number of processes terminated = " << terminated << endl;
    for (int i = 0; i < n; i++)
    {
        edfstatsfile << "The waiting time of Process P" << i + 1 << " is " << (starttime[i] - waitingtime[i]) / arr[i] << endl;
    }
}

int main()
{
    file.open("inp-params.txt");
    RMscheduling();
    file.close();
    t = 0;
    file.open("inp-params.txt");
    EDFscheduling();
    file.close();
}