#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Process {
    string id;
    int arrival, burst, remaining_burst;
};
void round_robin(vector<Process>& processes, int time_quantum) {
    int time = 0;
    vector<string> result;
    unordered_map<string, int> remaining_bt;
    unordered_map<string, int> completion_time;
    unordered_map<string, int> turnaround_time;
    unordered_map<string, int> waiting_time;

    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });
    queue<string> queue;
    int i = 0;
    while (i < processes.size() && processes[i].arrival <= time) {
        queue.push(processes[i].id);
        i++;
    }
    while (!queue.empty()) {
        string current_process = queue.front();
        queue.pop();
        Process* process_ptr = nullptr;
        for (auto& p : processes) {
            if (p.id == current_process) {
                process_ptr = &p;
                break;
            } }
        if (process_ptr->remaining_burst > time_quantum) {
            result.push_back(current_process + " (" + to_string(time) + "-" + to_string(time + time_quantum) + ")");
            time += time_quantum;
            process_ptr->remaining_burst -= time_quantum;
        } else {
            result.push_back(current_process + " (" + to_string(time) + "-" + to_string(time + process_ptr->remaining_burst) + ")");
            time += process_ptr->remaining_burst;
            completion_time[current_process] = time;
            process_ptr->remaining_burst = 0;
        }
        while (i < processes.size() && processes[i].arrival <= time) {
            queue.push(processes[i].id);
            i++;
        }
        if (process_ptr->remaining_burst > 0) {
            queue.push(current_process);
        }
    }
    for (auto& p : processes) {
        turnaround_time[p.id] = completion_time[p.id] - p.arrival;
        waiting_time[p.id] = turnaround_time[p.id] - p.burst;
    }
    cout << "Process  Arrival Time  Burst Time  Completion Time  Turn Around Time  Waiting Time" << endl;
    for (auto& p : processes) {
        cout << p.id << "\t\t" << p.arrival << "\t\t" << p.burst << "\t\t"
             << completion_time[p.id] << "\t\t" << turnaround_time[p.id] << "\t\t"
             << waiting_time[p.id] << endl;
    }
}
int main() {
    vector<Process> process_data = {
        {"P1", 0, 5, 5},
        {"P2", 1, 4, 4},
        {"P3", 2, 2, 2},
        {"P4", 4, 1, 1}
    };
    int time_quantum = 2;
    round_robin(process_data, time_quantum);
    return 0;
}
