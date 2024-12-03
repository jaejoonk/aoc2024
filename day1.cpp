#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool minsort(int i, int j) { return (i < j); }

int main() {
    vector<int> row1, row2;
    int entry;
    int maxdiff;

    string filename = "day1_input.txt";

    ifstream infile(filename);

    // part 1
    int index = 0;
    while (infile >> entry) {
        if (index % 2 == 0) {
            row1.emplace_back(entry);
        } else {
            row2.emplace_back(entry);
        }

        index++;
    }

    sort(row1.begin(), row1.end(), minsort);
    sort(row2.begin(), row2.end(), minsort);

    for (int i = 0; i < (index / 2); i++) {
        maxdiff += abs(row1[i] - row2[i]);
    }
    
    cout << "Maximum difference: " << maxdiff << endl;

    // part 2
    unordered_map<int,int> counts;
    long long int similarity = 0;

    for (int i = 0; i < (index / 2); i++) {
        if (counts.find(row1[i]) == counts.end()) {
            int hits = 0;
            for (int j = 0; j < (index / 2); j++) {
                if (row2[j] == row1[i]) { hits += 1; }
            }
            counts[row1[i]] = hits;
        }

        similarity += (long long int)(counts[row1[i]] * row1[i]);
    }

    cout << "Similarity score: " << similarity << endl;
    return 0;
}

