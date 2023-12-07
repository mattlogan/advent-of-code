#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int main() {
    ifstream file("2022/1/input.txt");

    int curCals;
    int maxCals = 0;

    while (file) {
        string line;
        getline(file, line);

        if (line.empty()) {
            maxCals = max(maxCals, curCals);
            curCals = 0;
        } else {
            curCals += stoi(line);
        }
    }
}
