#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    std::ifstream file("2023/1/input.txt");

    std::unordered_map<std::string, int> numbers;
    numbers["one"] = 1;
    numbers["two"] = 2;
    numbers["three"] = 3;
    numbers["four"] = 4;
    numbers["five"] = 5;
    numbers["six"] = 6;
    numbers["seven"] = 7;
    numbers["eight"] = 8;
    numbers["nine"] = 9;

    int sum = 0;

    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";

        if (line.empty()) {
            break;
        }

        int first = -1;
        int last;

        for (int i = 0; i < line.length(); i++) {
            char ch = line.at(i);
            if (ch >= '0' && ch <= '9') {
                int res = ch - '0';
                if (first == -1) {
                    first = ch - '0';
                }
                last = res;
                continue;
            }

            std::string curWord;
            int digit = -1;
            for (int j = i; j < line.length(); j++) {
                curWord += line.at(j);
                try {
                    digit = numbers.at(curWord);
                    break;
                } catch (const std::out_of_range &e) {
                    if (line.at(j) >= '0' && line.at(j) <= '9') {
                        break;
                    }
                }
            }
            if (digit != -1) {
                if (first == -1) {
                    first = digit;
                }
                last = digit;
            }
        }

        sum += 10 * first + last;
    }

    std::cout << sum;
}
