#include <iostream>
#include <fstream>
#include <string>

std::vector<long> getNums(std::string str) {
    std::vector<long> vec;
    long curValue = 0;
    bool hasValue = false;
    for (int i = 0; i < str.length(); i++) {
        if (std::isdigit(str[i])) {
            curValue = curValue * 10 + str[i] - '0';
            hasValue = true;
        }
        if (hasValue && str[i] == ' ' || i == str.length() - 1) {
            vec.push_back(curValue);
            curValue = 0;
            hasValue = false;
        }
    }
    return vec;
}

int main() {
    std::ifstream file("2023/5/input.txt");

    long minLocation = INT_MAX;
    int lineIndex = 0;

    std::vector<long> seeds;
    std::vector<std::vector<std::vector<long> > > maps;
    for (int i = 0; i < 7; i++) {
        maps.push_back(std::vector<std::vector<long> >());
    }

    std::string curMap;

    while (file) {
        std::string line;
        getline(file, line);
        std::cout << line << "\n";
        if (curMap == "humidity-to-location map:" && line.empty()) {
            break;
        }

        if (line.empty()) {
            continue;
        } else if (lineIndex == 0) {
            seeds = getNums(line);
        } else if (line.find("map:") != std::string::npos) {
            curMap = line;
        } else if (curMap == "seed-to-soil map:") {
            maps[0].push_back(getNums(line));
        } else if (curMap == "soil-to-fertilizer map:") {
            maps[1].push_back(getNums(line));
        } else if (curMap == "fertilizer-to-water map:") {
            maps[2].push_back(getNums(line));
        } else if (curMap == "water-to-light map:") {
            maps[3].push_back(getNums(line));
        } else if (curMap == "light-to-temperature map:") {
            maps[4].push_back(getNums(line));
        } else if (curMap == "temperature-to-humidity map:") {
            maps[5].push_back(getNums(line));
        } else if (curMap == "humidity-to-location map:") {
            maps[6].push_back(getNums(line));
        }

        lineIndex++;
    }

    for (long seed: seeds) {
        long value = seed;
        for (std::vector<std::vector<long> > map: maps) {
            for (std::vector<long> m: map) {
                if (value >= m[1] && value <= m[1] + m[2] - 1) {
                    value = value + (m[0] - m[1]);
                    break;
                }
            }
        }

        minLocation = std::min(minLocation, value);
    }

    std::cout << "min: " << minLocation << "\n";
}
