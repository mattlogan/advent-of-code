#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int priority(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a' + 1;
    } else if ('A' <= c && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

int main() {
    ifstream file("2022/3/input.txt");

    int sum = 0;
    int index = 0;
    unordered_set<char> firstSet;
    unordered_set<char> secondSet;

    while (file) {
        string line;
        getline(file, line);
        if (line.empty()) {
            break;
        }

        if (index == 0) {
            for (int i = 0; i < line.length(); i++) {
                firstSet.insert(line.at(i));
            }
        } else if (index == 1) {
            for (int i = 0; i < line.length(); i++) {
                secondSet.insert(line.at(i));
            }
        } else if (index == 2) {
            for (int i = 0; i < line.length(); i++) {
                char c = line.at(i);
                if (firstSet.count(c) > 0 && secondSet.count(c) > 0) {
                    sum += priority(c);
                    break;
                }
            }

            firstSet.clear();
            secondSet.clear();
        }

        index = (index + 1) % 3;
    }

    cout << sum;
}
