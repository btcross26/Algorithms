#ifndef _UNION_FIND_H
#define _UNION_FIND_H

#include <set>
#include <vector>

template<typename T>
class Union_find {
    public:
        Union_find(T high);                             // initialize high sites numbered from 1 to high
        Union_find(T low, T high);                      // initialize high - low + 1 sites with integer names low to high
        ~Union_find();
        void add_connection(T p, T q);                  // add connection between p and q
        bool connected(T p, T q);                       // returns true if p and q are connected (in same component)
        std::vector< std::set<T> > get_components();    // returns vector of component node sets
        T count_sites();                                // number of sites
        T count_components();                           // number of components
        
    private:
        bool valid_input(T p);          // checks that site number is valid
        std::set<T> *NULL_PTR;          // null pointer value (0), signifies a single node cluster
        T ind_low;                      // subtracted from node number to get member<sites> array_index
        T num_sites;                    // number of sites in data structure    
        T num_components;               // number of components in data structure (initially equal to number of sites)
        std::set<T> **sites;            // array of pointers to corresponding component std::sets
        
        // make copying illegal
        Union_find(const Union_find &src) {}
        Union_find &operator=(const Union_find &src) { return *this; }
};

#endif