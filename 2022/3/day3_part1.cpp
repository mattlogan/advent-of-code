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
    while (file) {
        string line;
        getline(file, line);
        if (line.empty()) {
            break;
        }

        int len = line.length();
        string first = line.substr(0, len / 2);
        string second = line.substr(len / 2, len / 2);

        unordered_set<char> secondSet;
        for (int i = 0; i < second.length(); i++) {
            secondSet.insert(second.at(i));
        }

        char dupe;
        for (int i = 0; i < first.length(); i++) {
            char c = first.at(i);
            if (secondSet.count(c) > 0) {
                dupe = c;
                break;
            }
        }

        sum += priority(dupe);
    }

    cout << sum;
}
