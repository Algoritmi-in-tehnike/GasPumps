#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

std::vector<std::pair<int, int>> intervals;
std::vector<std::pair<int, int>> acceptedIntervals;
std::set<std::pair<int, int>> acceptedIntervalsSet;

bool custom_comparator(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.first != b.first) {
        // Sort ascending by first element if they are different
        return a.first < b.first;
    }
    else {
        // Sort descending by second element if first elements are equal
        return a.second > b.second;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) return -1;

    std::ifstream infile(argv[1]);
    //std::ofstream outfile("output.txt");

    int x, r, L, G;
    std::string command;
    std::stringstream ss;

    if (infile.is_open()) {
        std::getline(infile, command);
        ss << command;
        ss >> L >> G;
        ss.clear();

        while (std::getline(infile, command)) {
            ss << command;
            ss >> x >> r;
            intervals.push_back(std::make_pair(x - r, x + r));
            ss.clear();
        }

        std::sort(intervals.begin(), intervals.end(), custom_comparator);

        // check if first and last interval are in range
        if (intervals[0].first != 0 || intervals[intervals.size() - 1].second != L) { 
            std::cout << "-1";
            return -1;
        }
        // check if all points are in range
        for (int i = 0; i < intervals.size() - 1; i++) {
            if (intervals[i].second < intervals[i + 1].first) {
                std::cout << "-1";
                return -1;
            }
        }

        //for (std::pair<int, int> i : intervals) std::cout << "[" << i.first << ", " << i.second << "]\n";

        acceptedIntervals.push_back(intervals[0]); // always accept the first interval
        acceptedIntervalsSet.insert(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            std::pair<int, int> bestPair = intervals[i];
            for (int j = i; j < intervals.size(); j++) {
                if (intervals[j].first <= acceptedIntervals[acceptedIntervals.size() - 1].second) {
                    if (bestPair.second <= intervals[j].second) bestPair = intervals[j];
                }
            }
            if (acceptedIntervalsSet.count(bestPair) == 0) {
                acceptedIntervals.push_back(bestPair);
                acceptedIntervalsSet.insert(bestPair);
            }
        }

        //for (std::pair<int, int> i : acceptedIntervals) std::cout << "[" << i.first << ", " << i.second << "]\n";

        std::cout << intervals.size() - acceptedIntervals.size() << "\n";
    }
}