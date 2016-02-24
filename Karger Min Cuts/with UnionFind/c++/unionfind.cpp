#include <set>
#include "unionfind.h"

using namespace std;
       
Unionfind::Unionfind(int sites) : SITES(sites) {
    this->num_clusters = sites;
    this->setptr = new set<int>*[sites];
    for(int i = 0; i < sites; ++i) {
        set<int> *c = new set<int>;
        c->insert(i + 1);
        this->setptr[i] = c;
    }
}

Unionfind::~Unionfind() {
    for(int i = 0; i < this->SITES; ++i) {
        if(this->setptr[i] != 0) {
            set<int> *old = this->setptr[i];
            for(int j = i; j < this->SITES; ++j) {
                if(this->setptr[j] == old) {
                    this->setptr[j] = 0;
                }
            }
        }
    }
    delete[] this->setptr;
}

bool Unionfind::is_connected(int n1, int n2) {
    return this->setptr[n1-1] == this->setptr[n2-1];
}

void Unionfind::merge(int n1, int n2) {
    if(!this->is_connected(n1, n2)) {
        typedef set<int>::iterator iter;
        --this->num_clusters;
        int n1_size = (this->setptr[n1-1])->size();
        int n2_size = (this->setptr[n2-1])->size();
        set<int> *old;
        if(n1_size >= n2_size) {
            old = this->setptr[n2-1];
            iter begin = (this->setptr[n2-1])->begin();
            iter end = (this->setptr[n2-1])->end();
            (this->setptr[n1-1])->insert(begin, end);
            for(iter it = begin; it != end; ++it) {
                this->setptr[*it - 1] = this->setptr[n1-1];
            }
        } else {
            old = this->setptr[n1-1];
            iter begin = (this->setptr[n1-1])->begin();
            iter end = (this->setptr[n1-1])->end();
            (this->setptr[n2-1])->insert(begin, end);
            for(iter it = begin; it != end; ++it) {
                this->setptr[*it - 1] = this->setptr[n2-1];
            }
        }
        delete old;
    }
}

int Unionfind::get_num_clusters() { return this->num_clusters; }

std::set<int> Unionfind::get_first_cluster() { return *(this->setptr[0]); }        
