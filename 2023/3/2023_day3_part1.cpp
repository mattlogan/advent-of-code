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

    int sum = 0;

    for (int y = 0; y < lines.size(); y++) {
        int value = 0;
        int valueStartPos = -1;
        std::string line = lines[y];
        for (int x = 0; x < line.length(); x++) {
            char c = line.at(x);
            if (std::isdigit(c)) {
                value = 10 * value + c - '0';
                if (valueStartPos == -1) {
                    valueStartPos = x;
                }

                if (x == line.length() - 1 || !std::isdigit(line[x + 1])) {
                    int valueEndPos = x;
                    bool isPart = false;

                    for (int x0 = valueStartPos - 1; x0 <= valueEndPos + 1; x0++) {
                        for (int y0 = y - 1; y0 <= y + 1; y0++) {
                            if (x0 < 0 || x0 >= line.length() || y0 < 0 || y0 >= lines.size()) {
                                continue;
                            }
                            if (y0 == y && (x0 >= valueStartPos && x0 <= valueEndPos)) {
                                continue;
                            }
                            if (lines[y0][x0] != '.' && !(std::isdigit(lines[y0][x0]))) {
                                isPart = true;
                            }
                        }
                    }

                    if (isPart) {
                        sum += value;
                    }

                    value = 0;
                    valueStartPos = -1;
                }
            }
        }
    }

    std::cout << "sum: " << sum;
}
