#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

void FCFS(int n, vector<int> &arrival_time, vector<int> &serve_time)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> finish_time(n + 1), response_time(n + 1), waiting_time(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pq.push({arrival_time[i], i});
    }
    int time = 0;
    while (!pq.empty())
    {
        if (pq.top().first > time)
            time = pq.top().first + serve_time[pq.top().second];
        else
            time += serve_time[pq.top().second];
        finish_time[pq.top().second] = time;
        pq.pop();
    }
    int sum_waiting_time = 0;
    for (int i = 1; i <= n; i++)
    {
        response_time[i] = finish_time[i] - arrival_time[i];
        waiting_time[i] = response_time[i] - serve_time[i];
        sum_waiting_time += waiting_time[i];
    }
    cout << "\n\tProcess\tArrival time\tServe time\tFinish time\tResponse time\tWaiting time\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "P" << i << ":\t" << arrival_time[i] << "\t\t" << serve_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << response_time[i] << "\t\t" << waiting_time[i] << "\n";
    }
    cout << "\nAverage waiting time: " << sum_waiting_time / (double)n << "\n";
}

void priority_pre(int n, vector<int> &arrival_time, vector<int> &serve_time, vector<int> &priority)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> finish_time(n + 1), response_time(n + 1), waiting_time(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pq.push({arrival_time[i], i});
    }
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq2;
    for (int time = 0; !pq.empty() || !pq2.empty(); time++)
    {
        while (!pq.empty() && pq.top().first <= time)
        {
            pq2.push({priority[pq.top().second], {serve_time[pq.top().second], pq.top().second}});
            pq.pop();
        }
        if (!pq2.empty())
        {
            if (pq2.top().second.first == 1)
            {
                finish_time[pq2.top().second.second] = time + 1;
                pq2.pop();
            }
            else
            {
                int p = pq2.top().second.second, s = pq2.top().second.first, pr = pq2.top().first;
                pq2.pop();
                pq2.push({pr, {s - 1, p}});
            }
        }
    }
    int sum_waiting_time = 0;
    for (int i = 1; i <= n; i++)
    {
        response_time[i] = finish_time[i] - arrival_time[i];
        waiting_time[i] = response_time[i] - serve_time[i];
        sum_waiting_time += waiting_time[i];
    }
    cout << "\n\tProcess\tArrival time\tServe time\tFinish time\tResponse time\tWaiting time\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "P" << i << ":\t" << arrival_time[i] << "\t\t" << serve_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << response_time[i] << "\t\t" << waiting_time[i] << "\n";
    }
    cout << "\nAverage waiting time: " << sum_waiting_time / (double)n << "\n";
}

void SJF(int n, vector<int> &arrival_time, vector<int> &serve_time)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> finish_time(n + 1), response_time(n + 1), waiting_time(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pq.push({arrival_time[i], i});
    }
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<>> pq2;
    int time = 0;
    while (!pq.empty() || !pq2.empty())
    {
        while (!pq.empty() && pq.top().first <= time)
        {
            pq2.push({{serve_time[pq.top().second], pq.top().first}, pq.top().second});
            pq.pop();
        }
        if (!pq2.empty())
        {
            time += serve_time[pq2.top().second];
            finish_time[pq2.top().second] = time;
            pq2.pop();
        }
        else
            time = pq.top().first;
    }
    int sum_waiting_time = 0;
    for (int i = 1; i <= n; i++)
    {
        response_time[i] = finish_time[i] - arrival_time[i];
        waiting_time[i] = response_time[i] - serve_time[i];
        sum_waiting_time += waiting_time[i];
    }
    cout << "\n\tProcess\tArrival time\tServe time\tFinish time\tResponse time\tWaiting time\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "P" << i << ":\t" << arrival_time[i] << "\t\t" << serve_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << response_time[i] << "\t\t" << waiting_time[i] << "\n";
    }
    cout << "\nAverage waiting time: " << sum_waiting_time / (double)n << "\n";
}

void round_robin(int n, vector<int> &arrival_time, vector<int> &serve_time, int quantum)
{
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<>> pq;
    vector<int> finish_time(n + 1), response_time(n + 1), waiting_time(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pq.push({{arrival_time[i], i}, serve_time[i]});
    }
    queue<pair<pair<int, int>, int>> q;
    pair<pair<int, int>, int> lst = {{-1, -1}, -1}, l = {{-1, -1}, -1};
    int time = 0;
    while (!pq.empty() || !q.empty() || lst != l)
    {
        while (!pq.empty() && pq.top().first.first <= time)
            q.push(pq.top()), pq.pop();
        if (lst != l)
        {
            q.push(lst);
            lst = l;
        }
        if (q.empty() && !pq.empty())
            time = pq.top().first.first, q.push(pq.top()), pq.pop();
        if (q.front().second <= quantum)
        {
            time += q.front().second;
            finish_time[q.front().first.second] = time;
            q.pop();
        }
        else
        {
            time += quantum;
            int p = q.front().first.second, a = q.front().first.first, s = q.front().second;
            q.pop();
            lst = {{a, p}, s - quantum};
        }
    }
    int sum_waiting_time = 0;
    for (int i = 1; i <= n; i++)
    {
        response_time[i] = finish_time[i] - arrival_time[i];
        waiting_time[i] = response_time[i] - serve_time[i];
        sum_waiting_time += waiting_time[i];
    }
    cout << "\n\tProcess\tArrival time\tServe time\tFinish time\tResponse time\tWaiting time\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "P" << i << ":\t" << arrival_time[i] << "\t\t" << serve_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << response_time[i] << "\t\t" << waiting_time[i] << "\n";
    }
    cout << "\nAverage waiting time: " << sum_waiting_time / (double)n << "\n";
}

int main(int argc, char *argv[])
{
    string algo = argv[1];
    int n;
    cin >> n;

    vector<int> arrival_time(n + 1), serve_time(n + 1), priority(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arrival_time[i] >> serve_time[i];
        if (algo == "priority")
        {
            cin >> priority[i];
        }
    }

    if (algo == "fcfs")
    {
        FCFS(n, arrival_time, serve_time);
    }
    else if (algo == "priority")
    {
        priority_pre(n, arrival_time, serve_time, priority);
    }
    else if (algo == "sjf")
    {
        SJF(n, arrival_time, serve_time);
    }
    else if (algo == "round_robin")
    {
        int quantum;
        cin >> quantum;
        round_robin(n, arrival_time, serve_time, quantum);
    }
    return 0;
}
