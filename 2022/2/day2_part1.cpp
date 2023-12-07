#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
A = rock
B = paper
C = scissors

X = rock
Y = paper
Z = scissors

rock = 1
paper = 2
scissors = 3

win = 6
draw = 3
loss = 0
*/
char decode(char c) {
    if (c == 'X') {
        return 'A';
    } else if (c == 'Y') {
        return 'B';
    } else {
        return 'C';
    }
}

int points(char c) {
    return c - 'A' + 1;
}

// A, B or B, C == true
// B, A, or C, B == false
// A, C == false
// C, A == true
int result(char first, char second) {
    int diff = second - first;
    if (diff == 0) {
        return 3;
    } else if (diff == 1 || diff == -2) {
        return 6;
    } else {
        return 0;
    }
}

int main() {
    ifstream file("2022/2/input.txt");

    int sum = 0;
    while (file) {
        string line;
        getline(file, line);

        if (line.empty()) {
            break;
        }

        char first = line.at(0);
        char second = decode(line.at(2));

        sum += points(second);
        sum += result(first, second);
    }

    cout << sum;
}
