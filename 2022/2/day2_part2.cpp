#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
A = rock
B = paper
C = scissors

X = lose
Y = draw
Z = win

rock = 1
paper = 2
scissors = 3

win = 6
draw = 3
loss = 0
*/
int points(char c) {
    return c - 'A' + 1;
}

char getShape(char other, char instruction) {
    if (instruction == 'Y') {
        // draw
        return other;
    } else if (instruction == 'X') {
        // lose
        char next = other - 1;
        if (next < 'A') {
            next = 'C';
        }
        return next;
    } else {
        // win
        char next = other + 1;
        if (next > 'C') {
            next = 'A';
        }
        return next;
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
        char second = line.at(2);

        char shape = getShape(first, second);

        sum += points(shape);

        if (second == 'Y') {
            sum += 3;
        } else if (second == 'Z') {
            sum += 6;
        }
    }

    cout << sum;
}
