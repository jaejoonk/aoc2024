#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

bool check_report(vector<int> report) {
	int size = (int)report.size();
	if (size <= 1) { return false; } 

	int current = report[0];
	bool increasing = (report[1] > report[0]);

	for (int i = 1; i < size; ++i) {
		if (abs(current - report[i]) > 3 || abs(current - report[i]) < 1) {
			return false;	
		}
		if (increasing ^ (report[i] > current)) {
			return false;
		}
		current = report[i];
	}
 
	return true;
}

vector<int> remove_one(vector<int> vec, int i) {
	vec.erase(vec.begin() + i);
	return vec;
}

bool check_report_lenient(vector<int> report) {
	int size = (int)report.size();
	if (size <= 1) { return false; }

	int current = report[0];
	bool increasing = (report[1] > report[0]);

	for (int i = 1; i < size; ++i) {
		// if failing, remove current level or previous
		bool failure_case = false;
		for (int j = i; j >= 0; j--) {
			failure_case = failure_case || check_report(remove_one(report, j));
		}

		if (abs(current - report[i]) > 3 || abs(current - report[i]) < 1) {
			return failure_case;
		}
		if (increasing ^ (report[i] > current)) {
			return failure_case;
		}
		current = report[i];
	}

	return true;
}

int main() {
	string filename = "day2_input.txt";
	ifstream infile(filename);

	int passes = 0;
	if (infile.good()) {
		string line;
		while (getline(infile, line)) {
			istringstream ss(line);
			int entry;
			vector<int> report = {};
			while (ss >> entry) {
				report.push_back(entry);
			}
			// uncomment if part 1:
			// if (check_report(report)) { passes++; }
			if (check_report_lenient(report)) { passes++; }
		}
	}
	
	cout << "Number of good reports: " << passes << endl;
	
	return 0;
}

