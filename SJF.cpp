#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    string id;
    int arrival, burst, completion, turnaround, waiting;
    bool completed = false;
};
bool compareBurst(Process a, Process b) {
    return a.burst < b.burst;
}
bool isCompleted(vector<Process> &completed, Process &p) {
    for (auto &c : completed) {
        if (c.id == p.id) return true;
    }
    return false;
}
bool isAvailable(vector<Process> &available, Process &p) {
    for (auto &a : available) {
        if (a.id == p.id) return true;
    }
    return false;
}

int main() {
    vector<Process> process_data = {
        {"P1", 2, 6},
        {"P2", 5, 2},
        {"P3", 1, 8},
        {"P4", 0, 3},
        {"P5", 4, 4}
    };

    int n = process_data.size();
    int current_time = 0;
    vector<Process> completed, available;
    vector<string> execution_order;

    while (completed.size() < n) {
        for (auto &process : process_data) {
            if (process.arrival <= current_time && !isCompleted(completed, process) && !isAvailable(available, process)) {
                available.push_back(process);
            }
        }

        if (!available.empty()) {
            sort(available.begin(), available.end(), compareBurst);
            Process current_process = available.front();
            available.erase(available.begin());

            execution_order.push_back(current_process.id);
            current_process.completion = current_time + current_process.burst;
            current_process.turnaround = current_process.completion - current_process.arrival;
            current_process.waiting = current_process.turnaround - current_process.burst;
            current_time = current_process.completion;

            completed.push_back(current_process);
        } else {
            current_time++;
        }
    }
    cout << "Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto &p : completed) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion
             << "\t\t" << p.turnaround << "\t\t" << p.waiting << endl;
    }

    return 0;
}

