#ifndef _UNIONFIND_H
#define _UNIONFIND_H

class Unionfind {
    public:
        struct subset {
            int parent;
            int rank;
        };
        
    public:
        const int SITES;
        
    private:
        int num_clusters;
        subset *setptr;
        
    public:
        Unionfind(int sites);
        ~Unionfind();
        bool is_connected(int n1, int n2);
        void merge(int n1, int n2);
        int find(int n1);
        int get_num_clusters();

    private: // make copying illegal
        Unionfind(const Unionfind &other) : SITES(other.SITES) {}
        Unionfind &operator=(const Unionfind &other) { return *this; }
};

#endif