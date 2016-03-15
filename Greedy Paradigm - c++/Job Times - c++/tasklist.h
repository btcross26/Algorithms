#ifndef _TASKLIST_H
#define _TASKLIST_H

#include <vector>

class Tasklist {
	public:
		Tasklist(std::vector< std::vector<int> > tasklist);
		void score_difference();
		void score_ratio();
		unsigned long long sum_weighted_completion_times();
		
	private:
		std::vector< std::vector<int> > tasks;
		std::vector< std::vector<double> > scores;		
};

#endif
