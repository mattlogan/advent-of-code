#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

std::unordered_set<int> getNums(std::string str) {
    std::unordered_set<int> set;
    int curValue = 0;
    for (int i = 0; i < str.length(); i++) {
        if (std::isdigit(str[i])) {
            curValue = curValue * 10 + str[i] - '0';
        }
        if (curValue > 0 && str[i] == ' ' || i == str.length() - 1) {
            set.insert(curValue);
            curValue = 0;
        }
    }
    return set;
}

int main() {
    std::ifstream file("2023/4/input.txt");

    std::unordered_map<int, int> extraCards;

    int lineIndex = 0;

    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";
        if (line.empty()) {
            break;
        }

        int colonPos = line.find(':');
        int barPos = line.find('|');

        int winningNumsStrStart = colonPos + 2;
        int winningNumsStrEnd = barPos - 1;
        std::string winningNumsStr = line.substr(winningNumsStrStart, winningNumsStrEnd - winningNumsStrStart);
        std::unordered_set<int> winningNums = getNums(winningNumsStr);

        int myNumsStrStart = barPos + 2;
        int myNumsStrEnd = line.length();
        std::string myNumsStr = line.substr(myNumsStrStart, myNumsStrEnd - myNumsStrStart);
        std::unordered_set<int> myNums = getNums(myNumsStr);

        int matches = 0;
        for (int num: myNums) {
            if (winningNums.count(num) > 0) {
                matches++;
            }
        }

        for (int i = lineIndex + 1; i <= lineIndex + matches; i++) {
            extraCards[i] = extraCards[i] + extraCards[lineIndex] + 1;
        }

        lineIndex++;
    }

    int sum = 0;
    for (int i = 0; i < lineIndex; i++) {
        sum += 1 + extraCards[i];
    }
    std::cout << "sum: " << sum << "\n";
}

