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
        if (intervals[0].first != 0 || intervals[G - 1].second != L) { 
            std::cout << "-1";
            return -1;
        }
        // check if all points are in range
        /*for (int i = 0; i < intervals.size() - 1; i++) {
            if (intervals[i].second < intervals[i + 1].first) {
                std::cout << "-1";
                return -1;
            }
        }*/

        //for (std::pair<int, int> i : intervals) std::cout << "[" << i.first << ", " << i.second << "]\n";

        {
            //int numOfAccepted = 1;
            //// current length to end of 1st interval
            //int currentLength = intervals[0].second;
            //// index of the last accepted gas station
            //int currentAcceptedIndex = 0;
            //// index of best next gas station
            //int currentBestIndex = -1;

            //while (currentLength < L) {
            //    currentBestIndex = -1;
            //    //currentBestIndex = currentAcceptedIndex;

            //    // if there are no more gas statons
            //    if (currentAcceptedIndex + 1 == G) {
            //        std::cout << "-1";
            //        return -1;
            //    }

            //    for (int i = currentAcceptedIndex + 1; i < G; i++) {
            //        //if (intervals[i].first > currentLength && currentBestIndex == -1) { // if nearest next gas station is not connected to the previous
            //        //    std::cout << "-1";
            //        //    return -2;
            //        //}

            //        //if (intervals[i].first <= currentLength || currentBestIndex == currentAcceptedIndex + 1) {  // if its connected
            //        //    if (intervals[i].second > intervals[currentBestIndex].second) currentBestIndex = i; // if it's longer, accept as current best answer
            //        //}
            //        if (intervals[i].first <= currentLength && (currentBestIndex == -1 || intervals[currentBestIndex].second <= intervals[i].second)) currentBestIndex = i;
            //        /*if (intervals[i].first <= currentLength && intervals[currentBestIndex].second <= intervals[i].second) {
            //            currentBestIndex = i;
            //        }*/
            //        else break;
            //    }

            //    // if we found a new best gas station
            //    //if (currentBestIndex > currentAcceptedIndex) {
            //    if (currentBestIndex != -1) {
            //        currentLength = intervals[currentBestIndex].second; // update values
            //        currentAcceptedIndex = currentBestIndex;
            //        numOfAccepted++;
            //    }
            //        
            //    //}
            //    //else {
            //    //    // if we didn't find a new best gas station, no other gas stations are connected to current length
            //    //    std::cout << "-1";
            //    //    return -1;
            //    //}

            //    /*currentLength = intervals[currentBestIndex].second;
            //    acceptedIntervals.push_back(intervals[currentBestIndex]);
            //    currentAcceptedIndex = currentBestIndex;*/
            //}
        }

        acceptedIntervals.push_back(intervals[0]); // always accept the first interval
        acceptedIntervalsSet.insert(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            std::pair<int, int> bestPair = intervals[i];
            for (int j = i; j < intervals.size(); j++) {
                if (intervals[j].first > acceptedIntervals[acceptedIntervals.size() - 1].second && j == i + 1) {
                    std::cout << "-1";
                    return -1;
                }

                if (intervals[j].first <= acceptedIntervals[acceptedIntervals.size() - 1].second) {
                    if (bestPair.second <= intervals[j].second) bestPair = intervals[j];
                }
                else break;
            }
            if (acceptedIntervalsSet.count(bestPair) == 0) {
                acceptedIntervals.push_back(bestPair);
                acceptedIntervalsSet.insert(bestPair);
                if (bestPair.second == L) goto print;
            }
        }

        //for (std::pair<int, int> i : acceptedIntervals) std::cout << "[" << i.first << ", " << i.second << "]\n";
        print:
        //std::cout << intervals.size() - numOfAccepted << "\n";
        std::cout << intervals.size() - acceptedIntervals.size() << "\n";
    }
}