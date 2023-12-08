#include <iostream>
#include <fstream>
#include <string>

struct Range {
    long start;
    long end;

    Range(long start, long end) : start(start), end(end) {}

    bool operator==(const Range &rhs) const {
        return start == rhs.start &&
               end == rhs.end;
    }

    bool operator!=(const Range &rhs) const {
        return !(rhs == *this);
    }
};

struct MapRange {
    long start;
    long end;
    long offset;

    MapRange(long start, long end, long offset) : start(start), end(end), offset(offset) {}
};

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

std::vector<Range> getSeeds(std::string str) {
    std::vector<long> nums = getNums(str);
    std::vector<Range> seeds;
    for (long i = 0; i < nums.size(); i += 2) {
        long start = nums[i];
        long range = nums[i + 1];
        seeds.push_back(Range(start, start + range - 1));
    }
    return seeds;
}

MapRange getMaps(std::string str) {
    std::vector<long> nums = getNums(str);
    long range = nums[2];
    return MapRange(nums[1], nums[1] + range - 1, nums[0] - nums[1]);
}

int main() {
    std::ifstream file("2023/5/input.txt");

    int lineIndex = 0;

    std::vector<Range> sources;
    std::vector<std::vector<MapRange> > maps;
    for (int i = 0; i < 7; i++) {
        maps.push_back(std::vector<MapRange>());
    }

    std::string curMap;
    int curMapIndex = -1;

    while (file) {
        std::string line;
        getline(file, line);
        if (curMap == "humidity-to-location map:" && line.empty()) {
            break;
        }

        if (line.empty()) {
            continue;
        } else if (lineIndex == 0) {
            sources = getSeeds(line);
        } else if (line.find("map:") != std::string::npos) {
            curMap = line;
            curMapIndex++;
        } else {
            maps[curMapIndex].push_back(getMaps(line));
        }

        lineIndex++;
    }

    for (std::vector<MapRange> mapRanges: maps) {
        std::vector<Range> nextSources;
        for (Range sourceRange: sources) {
            std::vector<Range> remaining;
            bool addedFullRangeToRemaining = false;
            // go thru map and map overlaps of current source range to new range, add to next
            for (MapRange mapRange: mapRanges) {
                bool startInRange = sourceRange.start >= mapRange.start && sourceRange.start <= mapRange.end;
                bool endInRange = sourceRange.end >= mapRange.start && sourceRange.end <= mapRange.end;
                long offset = mapRange.offset;

                if (sourceRange.start > mapRange.end) {
                    // no overlap
                    if (!addedFullRangeToRemaining) {
                        remaining.push_back(Range(sourceRange.start, sourceRange.end));
                        addedFullRangeToRemaining = true;
                    }
                } else if (sourceRange.end < mapRange.start) {
                    // no overlap
                    if (!addedFullRangeToRemaining) {
                        remaining.push_back(Range(sourceRange.start, sourceRange.end));
                        addedFullRangeToRemaining = true;
                    }
                } else if (startInRange && endInRange) {
                    Range next(sourceRange.start + offset, sourceRange.end + offset);
                    // source range is entirely inside map range
                    nextSources.push_back(next);
                    // no more remaining in source range
                    remaining.clear();
                } else if (startInRange) {
                    // just start of source range is inside map range
                    nextSources.push_back(Range(sourceRange.start + offset, mapRange.end + offset));
                    // add everything after map range to remaining
                    remaining.push_back(Range(mapRange.end + 1, sourceRange.end));
                } else if (endInRange) {
                    // just end of source range is inside map range
                    nextSources.push_back(Range(mapRange.start + offset, sourceRange.end + offset));
                    // update remaining
                    remaining.push_back(Range(mapRange.end + 1, sourceRange.end));
                } else {
                    // source range surrounds map range
                    nextSources.push_back(Range(mapRange.start + offset, mapRange.end + offset));
                    // update remaining
                    remaining.push_back(Range(sourceRange.start, mapRange.start - 1));
                    remaining.push_back(Range(mapRange.end + 1, sourceRange.end));
                }

                // update anything in remaining that overlaps with map range
                std::vector<Range> updatedRemaining;
                for (Range r: remaining) {
                    if (r.start >= mapRange.start && r.end <= mapRange.end) {
                        // fully in range, ignore
                    } else if (r.start < mapRange.start && r.end >= mapRange.start && r.end <= mapRange.end) {
                        updatedRemaining.push_back(Range(r.start, mapRange.start - 1));
                    } else if (r.start >= mapRange.start && r.start <= mapRange.end && r.end > mapRange.end) {
                        updatedRemaining.push_back(Range(mapRange.end + 1, r.end));
                    } else if (r.start < mapRange.start && r.end > mapRange.end) {
                        updatedRemaining.push_back(Range(r.start, mapRange.start - 1));
                        updatedRemaining.push_back(Range(mapRange.end + 1, r.end));
                    }
                }
                remaining = updatedRemaining;
            }

            // add all remaining to next
            for (Range r: remaining) {
                nextSources.push_back(r);
            }
        }

        sources = nextSources;
    }

    long min = LONG_MAX;
    for (Range s: sources) {
        min = std::min(min, s.start);
    }

    std::cout << "min: " << min << "\n";
}
