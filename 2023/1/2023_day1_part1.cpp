#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("2023/1/input.txt");

    int sum = 0;

    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";

        if (line.empty()) {
            break;
        }

        int first = -1;
        int last = -1;

        for (char ch: line) {
            if (ch >= '0' && ch <= '9') {
                int res = ch - '0';
                if (first == -1) {
                    first = ch - '0';
                }
                last = res;
            }
        }

        sum += 10 * first + last;
    }

    std::cout << sum;
}
