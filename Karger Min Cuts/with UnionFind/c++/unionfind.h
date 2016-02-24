#ifndef _UNIONFIND_H
#define _UNIONFIND_H

#include <set>

class Unionfind {
    public:
        const int SITES;
        
    private:
        int num_clusters;
        std::set<int> **setptr;
        
    public:
        Unionfind(int sites);
        ~Unionfind();
        bool is_connected(int n1, int n2);
        void merge(int n1, int n2);
        int get_num_clusters();
        std::set<int> get_first_cluster();

    private: // make copying illegal
        Unionfind(const Unionfind &other) : SITES(other.SITES) {}
        Unionfind &operator=(const Unionfind &other) { return *this; }
};

#endif