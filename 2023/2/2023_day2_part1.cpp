#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("2023/2/input.txt");

    int id = 1;
    int sum = 0;

    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";
        if (line.empty()) {
            break;
        }

        line += ';';
        bool valid = true;
        int start = line.find(':', 0) + 2;

        while (true) {
            int end = line.find(';', start + 1);

            int value = 0;
            int numBlue = 0;
            int numRed = 0;
            int numGreen = 0;

            for (int i = start; i < end; i++) {
                char c = line.at(i);
                if (std::isdigit(c)) {
                    value = value * 10 + line.at(i) - '0';
                } else if (line.substr(i, 4) == "blue") {
                    numBlue = value;
                    value = 0;
                } else if (line.substr(i, 3 ) == "red") {
                    numRed = value;
                    value = 0;
                } else if (line.substr(i, 5) == "green") {
                    numGreen = value;
                    value = 0;
                }
            }

            if (numRed > 12 || numGreen > 13 || numBlue > 14) {
                valid = false;
                break;
            }

            if (end == line.length() - 1) {
                break;
            } else {
                start = end + 2;
            }
        }

        if (valid) {
            std::cout << "game is valid: " << id << "\n";
            sum += id;
        }

        id++;
    }

    std::cout << "sum: " << sum;
}
