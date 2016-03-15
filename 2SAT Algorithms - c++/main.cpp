#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include "graph.h"

using namespace std;

void read_2SAT_graph(Digraph &digraph, const char* filename);
bool check_2SAT_components(const vector< vector<int> > &components);

// argv 1-6 should be: 2sat1.txt 2sat2.txt 2sat3.txt 2sat4.txt 2sat5.txt 2sat6.txt
int main(int argc, char **argv) {
    clock_t start, finish;
    
    bool answers[6];
    Digraph digraph;
    for(int i = 1; i <= 6; ++i) {
        Digraph *digraph = new Digraph();
        cout << "Reading file: " << argv[i] << endl;
        start = clock();
        read_2SAT_graph(*digraph, argv[i]);
        finish = clock();
        cout << "Time to read file: " << 1e3 * (finish - start) / CLOCKS_PER_SEC
             << " ms" << endl;
        cout << "Calculating strongly connected components..." << endl;
        start = clock();
        vector< vector<int> > sccs = digraph->kosaraju_sccs();
        finish = clock();
        cout << "Calculation time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC
             << " ms" << endl;
        cout << "Checking 2SAT satisfiability..." << endl;
        start = clock();
        answers[i-1] = check_2SAT_components(sccs);
        finish = clock();
        cout << "Checking time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC
             << " ms" << endl;
        cout << "Satisfiable?: ";
        if(answers[i-1]) {
            cout << "Yes";
        } else {
            cout << "No";
        }
        cout << endl << endl;        
        delete digraph;
    }
    
    // Answer string
    cout << "Answer string: ";
    for(int i = 0; i < 6; ++i) {
        if(answers[i]) cout << "1";
        else cout << "0";
    }
    cout << endl << endl;
    
    return 0;
}

void read_2SAT_graph(Digraph &digraph, const char* filename) {
    ifstream input_file;
    input_file.open(filename);
    int tail, head, num_2SATS;
    input_file >> num_2SATS;
    while(input_file >> tail >> head) {
        digraph.add_edge(-tail, head);
        digraph.add_edge(-head, tail);
    }
    input_file.close();
}

bool check_2SAT_components(const vector< vector<int> > &components) {
    typedef vector< vector<int> >::const_iterator iter1;
    typedef vector<int>::const_iterator iter2;
    for(iter1 it1 = components.begin(); it1 != components.end(); ++it1) {
        vector<int> scc_abs = vector<int>();
        for(iter2 it2 = it1->begin(); it2 != it1->end(); ++it2) {
            scc_abs.push_back(abs(*it2));
        }
        set<int> check_set = set<int>(scc_abs.begin(), scc_abs.end());
        if(check_set.size() < scc_abs.size()) return false;
    }
    return true;
}