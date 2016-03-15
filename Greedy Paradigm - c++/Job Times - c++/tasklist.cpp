#include <iostream>
#include <vector>
#include <algorithm>
#include "tasklist.h"

Tasklist::Tasklist(std::vector< std::vector<int> > tasklist)
	: tasks(tasklist) {}


	
void Tasklist::score_difference() {
	std::vector<double> score_tuple;
	int job_number = 0, score;
	
	scores.clear();
	for(std::vector< std::vector<int> >::iterator job = tasks.begin();
		job != tasks.end(); job++) {
		score = (*job)[0] - (*job)[1];
		score_tuple.push_back(score);
		score_tuple.push_back((*job)[0]);
		score_tuple.push_back(job_number);
		scores.push_back(score_tuple);
		score_tuple.clear();
		job_number++;
	}
}



void Tasklist::score_ratio() {
	std::vector<double> score_tuple;
	int job_number = 0;
	double score;
	
	scores.clear();
	for(std::vector< std::vector<int> >::iterator job = tasks.begin();
		job != tasks.end(); job++) {
		score = 1.0 * (*job)[0] / (*job)[1];
		score_tuple.push_back(score);
		score_tuple.push_back(job_number);
		scores.push_back(score_tuple);
		score_tuple.clear();
		job_number++;
	}
}



unsigned long long Tasklist::sum_weighted_completion_times() {
	if(scores.empty()) {
		std::cerr << "\nScores have not yet been calculated!!!\n";
		return -1;
	}
	
	int job;
	unsigned long long completion_time = 0, sum = 0;
	
	std::sort(scores.begin(), scores.end());
	std::reverse(scores.begin(), scores.end());
	
	for(std::vector< std::vector<double> >::iterator score = scores.begin();
		score != scores.end(); score++) {
		job = (int)(*score).back();
		completion_time += tasks[job][1];
		sum += tasks[job][0] * completion_time;
	}
	
	return sum;	
}
