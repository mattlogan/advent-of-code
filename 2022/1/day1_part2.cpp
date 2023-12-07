#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int main() {
    ifstream file("2022/1/input.txt");

    priority_queue<int, vector<int>, greater<int> > pq;
    int cur = 0;

    while (file) {
        string line;
        getline(file, line);

        if (line.empty()) {
            pq.push(cur);
            if (pq.size() > 3) {
                pq.pop();
            }
            cur = 0;
        } else {
            cur += stoi(line);
        }
    }

    int sum = 0;
    while (!pq.empty()) {
        sum += pq.top();
        pq.pop();
    }

    cout << sum;
}
