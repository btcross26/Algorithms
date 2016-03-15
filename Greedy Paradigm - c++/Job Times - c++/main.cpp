#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "txtfileio.h"
#include "tasklist.h"

using namespace std;
using namespace txtfileio;

vector< vector<int> > read_tasks(string filename);

int main() {
	vector< vector<int> > tasks = read_tasks("jobs.txt");
	Tasklist tasklist(tasks);
	unsigned long long sum;
	
	// Question 1
	tasklist.score_difference();
	sum = tasklist.sum_weighted_completion_times();
	cout << "\nScore Type = Difference\n" << "Score: " << sum << endl << endl;
	
	// Question 2
	tasklist.score_ratio();
	sum = tasklist.sum_weighted_completion_times();
	cout << "Score Type = Ratio\n" << "Score: " << sum << endl << endl;
	
	return 0;
}


vector< vector<int> > read_tasks(string filename) {
	vector<int> task;
	vector< vector<int> > tasks;
	vector<string> lines = readlines(filename), tokens;

	for(int i = 1; i < lines.size(); i++) {
		tokenize(lines[i], tokens);
		task.push_back(atoi(tokens[0].c_str()));
		task.push_back(atoi(tokens[1].c_str()));
		tasks.push_back(task);
		tokens.clear();
		task.clear();		
	}

	return tasks;
}
