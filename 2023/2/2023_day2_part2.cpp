#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("2023/2/input.txt");

    long sum = 0;

    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";
        if (line.empty()) {
            break;
        }

        int value = 0;
        int maxBlue = 0;
        int maxRed = 0;
        int maxGreen = 0;

        for (int i = line.find(':'); i < line.length(); i++) {
            char c = line.at(i);
            if (std::isdigit(c)) {
                value = value * 10 + line.at(i) - '0';
            } else if (line.substr(i, 4) == "blue") {
                maxBlue = std::max(value, maxBlue);
                value = 0;
            } else if (line.substr(i, 3) == "red") {
                maxRed = std::max(value, maxRed);
                value = 0;
            } else if (line.substr(i, 5) == "green") {
                maxGreen = std::max(value, maxGreen);
                value = 0;
            }
        }

        long power = maxBlue * maxRed * maxGreen;
        sum += power;
    }

    std::cout << "sum: " << sum;
}
