#include "unionfind.h"

using namespace std;
       
Unionfind::Unionfind(int sites) : SITES(sites) {
    this->num_clusters = sites;
    this->setptr = new subset[sites];
    for(int i = 0; i < sites; ++i) {
        this->setptr[i] = Unionfind::subset();
        this->setptr[i].parent = i + 1;
        this->setptr[i].rank = 1;
    }
}

Unionfind::~Unionfind() { delete[] this->setptr; }

bool Unionfind::is_connected(int n1, int n2) {
    return this->find(n1) == this->find(n2);
}

void Unionfind::merge(int n1, int n2) {
    if(!this->is_connected(n1, n2)) {
        --this->num_clusters;
        subset *n1_root = &this->setptr[this->find(n1) - 1];
        subset *n2_root = &this->setptr[this->find(n2) - 1];
        if(n1_root->rank >= n2_root->rank) {
            n2_root->parent = n1_root->parent;
            n1_root->rank += n2_root->rank;
        } else {
            n1_root->parent = n2_root->parent;
            n2_root->rank += n1_root->rank;
        }
    }
}

int Unionfind::find(int n1) {
    if(this->setptr[n1-1].parent != n1) {
        setptr[n1-1].parent = this->find(setptr[n1-1].parent);
    }
    return this->setptr[n1-1].parent;
}

int Unionfind::get_num_clusters() { return this->num_clusters; }   
