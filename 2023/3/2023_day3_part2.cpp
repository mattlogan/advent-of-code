#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("2023/3/input.txt");

    std::vector<std::string> lines;
    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";
        if (line.empty()) {
            break;
        }
        lines.push_back(line);
    }

    long sum = 0;

    for (int y = 0; y < lines.size(); y++) {
        std::string line = lines[y];
        for (int x = 0; x < line.length(); x++) {
            if (line[x] != '*') {
                continue;
            }
            std::vector<int> adjacent;
            int curValue = 0;
            bool curIsAdjacent = false;

            if (y > 0) {
                for (int x0 = 0; x0 < line.length(); x0++) {
                    if (std::isdigit(lines[y - 1][x0])) {
                        curValue = curValue * 10 + lines[y - 1][x0] - '0';
                        if (std::abs(x0 - x) <= 1) {
                            curIsAdjacent = true;
                        }
                    }
                    if (curValue > 0 && (!std::isdigit(lines[y - 1][x0]) || x0 == line.length() - 1)) {
                        if (curIsAdjacent) {
                            adjacent.push_back(curValue);
                        }
                        curValue = 0;
                        curIsAdjacent = false;
                    }
                }
            }

            if (y < lines.size() - 1) {
                for (int x0 = 0; x0 < line.length(); x0++) {
                    if (std::isdigit(lines[y + 1][x0])) {
                        curValue = curValue * 10 + lines[y + 1][x0] - '0';
                        if (std::abs(x0 - x) <= 1) {
                            curIsAdjacent = true;
                        }
                    }
                    if (curValue > 0 && (!std::isdigit(lines[y + 1][x0]) || x0 == line.length() - 1)) {
                        if (curIsAdjacent) {
                            adjacent.push_back(curValue);
                        }
                        curValue = 0;
                        curIsAdjacent = false;
                    }
                }
            }

            for (int x0 = 0; x0 < x; x0++) {
                if (std::isdigit(line[x0])) {
                    curValue = curValue * 10 + line[x0] - '0';
                    if (std::abs(x0 - x) <= 1) {
                        curIsAdjacent = true;
                    }
                }
                if (curValue > 0 && (!std::isdigit(line[x0]) || x0 == x - 1)) {
                    if (curIsAdjacent) {
                        adjacent.push_back(curValue);
                    }
                    curValue = 0;
                    curIsAdjacent = false;
                }
            }

            if (x < line.length() - 1 && std::isdigit(line[x + 1])) {
                for (int x0 = x + 1; x0 < line.length(); x0++) {
                    if (std::isdigit(line[x0])) {
                        curValue = curValue * 10 + line[x0] - '0';
                    }
                    if (curValue > 0 && (!std::isdigit(line[x0]) || x0 == line.length() - 1)) {
                        adjacent.push_back(curValue);
                        break;
                    }
                }
            }

            if (adjacent.size() == 2) {
                long product = adjacent[0] * adjacent[1];
                sum += product;
            }
        }
    }


    std::cout << "sum: " << sum;
}
