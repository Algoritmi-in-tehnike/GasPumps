#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

std::vector<std::pair<int, int>> intervals;
std::vector<std::pair<int, int>> acceptedIntervals;

bool custom_comparator(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first != b.first) {
        return a.first < b.first;   // Sort ascending by first element if they are different
    }
    else {
        return a.second > b.second; // Sort descending by second element if first elements are equal
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) return -1;

    std::ifstream infile(argv[1]);

    int x, r, L, G, numOfAccepted = 1;
    std::string command;
    std::stringstream ss;

    if (infile.is_open()) {
        std::getline(infile, command);
        ss << command;
        ss >> L >> G;
        ss.clear();

        while (std::getline(infile, command)) { // read intervals and fill the vector
            ss << command;
            ss >> x >> r;
            intervals.push_back(std::make_pair(x - r, x + r));
            ss.clear();
        }

        std::sort(intervals.begin(), intervals.end(), custom_comparator);

        std::pair<int, int> bestInterval = intervals[0]; // always accept the first interval
        std::pair<int, int> lastAcceptedInterval = intervals[0];

        for (int i = 1; i < G; i++) {
            for (int j = i; j < G; j++) {
                if (intervals[j].first <= lastAcceptedInterval.second) {    // if interval is connected to the last accepted interval
                    if (bestInterval.second < intervals[j].second) bestInterval = intervals[j]; // if interval is longer than the current best interval, asign it
                }
                else if (i + 1 == G && lastAcceptedInterval.second < L) {   // if there wasn't a connected interval and we've reached the end, return -1
                    std::cout << "-1";
                    return 1;
                }
                else break; // if interval is not connected and we didn't check all, break the loop
            }
            if (bestInterval != lastAcceptedInterval) { // if current best pair isn't the last accepted, accept it
                lastAcceptedInterval = bestInterval;
                numOfAccepted++;
                if (bestInterval.second >= L) goto print;
            }
        }

        if (lastAcceptedInterval.second < L) {
            std::cout << "-1";
            return 2;
        }

        print:
        std::cout << G - numOfAccepted;
    }
}