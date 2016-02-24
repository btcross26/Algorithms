#include <iostream>
#include <set>
#include <vector>
#include "union_find.h"

// public member definitions
template<typename T>
Union_find<T>::Union_find(T high) : NULL_PTR(0) {
    (*this).num_sites = high;
    if(high < 1) {
        std::cerr << "Invalid high argument!" << std::endl;
        exit(1);
    }
    (*this).ind_low = 1;
    (*this).num_components = (*this).num_sites;
    (*this).sites = new std::set<T>*[(*this).num_sites];
    for(T i = 0; i < num_sites; i++) {
        (*this).sites[i] = (*this).NULL_PTR;
    }
}


template<typename T>
Union_find<T>::Union_find(T low, T high) : NULL_PTR(0) {
    (*this).num_sites = high - low + 1;
    if(high <= low || high - low < 1) {
        std::cerr << "Invalid arguments!" << std::endl;
        exit(1);
    }
    (*this).ind_low = low;
    (*this).num_components = (*this).num_sites;
    (*this).sites = new std::set<T>*[(*this).num_sites];
    for(T i = 0; i < num_sites; i++) {
        (*this).sites[i] = (*this).NULL_PTR;
    }
}


template<typename T>
Union_find<T>::~Union_find() {
    std::set<std::set<T>*> set_pointers;
    std::set<T> *pointer;
    typedef typename std::set<std::set<T>*>::iterator iter_set_p;
    
    // collect set pointers and set pointers in (*this).sites to NULL_PTR
    for(T i = 0; i < (*this).num_sites; i++) {
        if((*this).sites[i]) {
            pointer = (*this).sites[i];
            for(T j = i; j < (*this).num_sites; j++) {
                if((*this).sites[j] == pointer) {
                    (*this).sites[j] = (*this).NULL_PTR;
                }
            }
            delete pointer;
        }
    }
    
    // delete sites array of null pointers
    delete[] (*this).sites;
}


template<typename T>
void Union_find<T>::add_connection(T p, T q) {
    T pind = p - (*this).ind_low, qind = q - (*this).ind_low;
    if(!(*this).valid_input(p) || !(*this).valid_input(q)) {
        std::cerr << "Argument out of range!" << std::endl;
        return;
    }
    
    // check for connection to prevent dangling pointer in last if-else branch
    if((*this).connected(p, q)) {
        return;
    }
    
    if((*this).sites[pind] == (*this).NULL_PTR && (*this).sites[qind] == (*this).NULL_PTR) {
        (*this).sites[pind] = new std::set<T>;
        (*this).sites[qind] = (*this).sites[pind];
        (*(*this).sites[pind]).insert(p);
        (*(*this).sites[pind]).insert(q);
        --(*this).num_components;
    } else if((*this).sites[pind] == (*this).NULL_PTR) {
        (*this).sites[pind] = (*this).sites[qind];
        (*(*this).sites[qind]).insert(p);
        --(*this).num_components;
    }
    else if((*this).sites[qind] == (*this).NULL_PTR) {
        (*this).sites[qind] = (*this).sites[pind];
        (*(*this).sites[pind]).insert(q);
        --(*this).num_components;
    } else {
        typename std::set<T>::size_type psize = (*(*this).sites[pind]).size();
        typename std::set<T>::size_type qsize = (*(*this).sites[qind]).size();
        std::set<T> *old_set = (*this).NULL_PTR, *new_set = (*this).NULL_PTR;
        typedef typename std::set<T>::iterator iter_set;
        if(psize >= qsize) {
            new_set = (*this).sites[pind];
            old_set = (*this).sites[qind];
        } else {
            new_set = (*this).sites[qind];
            old_set = (*this).sites[pind];
        }
        (*new_set).insert((*old_set).begin(), (*old_set).end());
        for(iter_set it = (*old_set).begin(); it != (*old_set).end(); ++it) {
            (*this).sites[*it - (*this).ind_low] = new_set;
        }
        delete old_set;
        --(*this).num_components;
    }
}


template<typename T>
bool Union_find<T>::connected(T p, T q) {
    T pind = p - (*this).ind_low, qind = q - (*this).ind_low;
    return ((*this).sites[pind] == (*this).sites[qind] && (*this).sites[pind] != (*this).NULL_PTR);
}


template<typename T>
T Union_find<T>::count_sites() {
    return (*this).num_sites;
}


template<typename T>
T Union_find<T>::count_components() {
    return (*this).num_components;
}


template<typename T>
std::vector< std::set<T> > Union_find<T>::get_components() {
    std::set<T> explored;
    std::set<T> current_component;
    std::vector< std::set<T> > component_sets;
    std::set<T> *set_pointer;
    
    for(int i = 0; i < (*this).num_sites; i++) {
        if(explored.find(i + (*this).ind_low) != explored.end()) {
            continue;
        }
        set_pointer = (*this).sites[i];
        current_component.insert(i + (*this).ind_low);
        explored.insert(i + (*this).ind_low);
        if(set_pointer != (*this).NULL_PTR) {
            for(int j = i; j != (*this).num_sites; j++) {
                if((*this).sites[j] == set_pointer) {
                    current_component.insert(j + (*this).ind_low);
                    explored.insert(j + (*this).ind_low);                
                }
            }
        }
        component_sets.push_back(current_component);
        current_component.clear();
    }    
    return component_sets;
}

// private member definitions
template<typename T>
bool Union_find<T>::valid_input(T p) {
    return (p >= (*this).ind_low && p < (*this).num_sites + (*this).ind_low);
}

// dummy instantiations
template class Union_find<int>;
template class Union_find<long>;