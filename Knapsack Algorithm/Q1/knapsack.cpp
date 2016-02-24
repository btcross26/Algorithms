#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include "knapsack.h"

// public function definitions
template<typename T>
Knapsack<T>::Knapsack(const std::map<T, std::vector<T> > &items, T sack_size)
: NUM_ITEMS(items.size()), SACK_SIZE(sack_size), solution_complete(false) {
    typedef typename std::map<T, std::vector<T> >::const_iterator iter;

    int index = 0;
    (*this).max_weight = 0;
    (*this).item_list = new Item[(*this).NUM_ITEMS];
    for(iter it = items.begin(); it != items.end(); ++it) {
        (*this).item_list[index].item_no = (*it).first;
        if((*it).second[1] > 0) {
            (*this).item_list[index].item_weight = (*it).second[1];
            if((*this).max_weight < (*it).second[1]) {
                (*this).max_weight = (*it).second[1];
            }
        } else {
            std::cerr << "Item weights must be positive!" << std::endl;
            exit(1);
        }
        (*this).item_list[index].item_value = (*it).second[0];
        ++index;
    }
}


template<typename T>
Knapsack<T>::~Knapsack() {
    delete[] (*this).item_list;
}


template<typename T>
T Knapsack<T>::get_solution() {
    if(!solution_complete) {
        (*this).solve();
        (*this).solution_complete = true;
    }
    return (*this).solution;    
}



// private function definitions

/* 
Hidden type Matrow for sparse storage of matrix rows to use in solve() member function.
*/
template<typename T>
class Matrow {
        public:
            struct Entry{
                T weight;
                T value;
            };
            
            struct entry_comp {
                bool operator()(const Entry &e1, const Entry &e2) {
                    if(e1.weight == e2.weight) {
                        return e1.value > e2.value;
                    } else {
                        return e1.weight < e2.weight;
                    }
                }
            };
            
        public:
            typedef typename std::vector<Entry>::iterator iterator;
            iterator begin() { return (*this).entries.begin(); }
            iterator end() { return (*this).entries.end(); }
            
        public:
            Matrow() {
                Entry initial_entry = {0, 0};
                (*this).entries.push_back(initial_entry);
            }
            
            void add_entries(const std::vector<Entry> &new_entries) {
                std::vector<Entry> temp_vec;
                T previous_value = -1;
                
                std::copy(new_entries.begin(), new_entries.end(), std::back_inserter((*this).entries));
                std::sort((*this).entries.begin(), (*this).entries.end(), entry_comp());
                for(iterator it = (*this).entries.begin(); it != (*this).entries.end(); it++) {
                    if((*it).value <= previous_value) {
                        continue;
                    }
                    temp_vec.push_back(*it);
                    previous_value = (*it).value;
                }
                (*this).entries.swap(temp_vec);
            }
           
            T get_value(T item_weight) {
                T value = 0;
                for(iterator it = (*this).entries.begin(); it != (*this).entries.end(); ++it) {
                    if((*it).weight > item_weight) {
                        break;
                    }
                    value = (*it).value;
                }
                return value;
            }
            
            Entry back() {
                return (*this).entries.back();
            }
                             
        private:
            std::vector<Entry> entries;
};


template<typename T>
void Knapsack<T>::solve() {     // function only calculates optimal value -- does not track item list at this time   
    // create row object
    Matrow<T> entries;
    Matrow<T>::Entry entry;
  
    // declare remaining variables
    Knapsack<T>::Item current_item;
    std::vector< Matrow<T>::Entry > new_entries;
    T weight, value;
    
    // loop assumes items are sorted in increasing order by weight, then in decreasing order by value
    std::sort((*this).item_list, (*this).item_list + (*this).NUM_ITEMS, (*this).Item_sort_by_weight());

    for(int i = 0; i < (*this).NUM_ITEMS; ++i) {
        current_item = (*this).item_list[i];
        for(Matrow<T>::iterator it = entries.begin(); it != entries.end(); ++it) {
            weight = (*it).weight + current_item.item_weight;
            if(weight > (*this).SACK_SIZE) {
                break;
            }
            value = current_item.item_value + (*it).value;
            if(value > entries.get_value(weight)) {
                entry.weight = weight;
                entry.value = value;
                new_entries.push_back(entry);
            }
        }
        entries.add_entries(new_entries);
        new_entries.clear();
    }
    (*this).solution = entries.back().value;
}


template<typename T>
void Knapsack<T>::test() {
    std::cout << std::endl << "Testing sort functions..." << std::endl << std::endl;
    
    std::sort((*this).item_list, (*this).item_list + (*this).NUM_ITEMS, (*this).Item_sort_by_item_no());
    for(int i = 0; i < 5; i++) {
        std::cout << "Item number: " << (*this).item_list[i].item_no << std::endl;
    }
    std::cout << std::endl;
    
    std::sort((*this).item_list, (*this).item_list + (*this).NUM_ITEMS, (*this).Item_sort_by_value());
    for(int i = 0; i < 5; i++) {
        std::cout << "Item value: " << (*this).item_list[i].item_value << std::endl;
    }
    std::cout << std::endl;
    
    std::sort((*this).item_list, (*this).item_list + (*this).NUM_ITEMS, (*this).Item_sort_by_weight());
    for(int i = 0; i < 5; i++) {
        std::cout << "Item weight: " << (*this).item_list[i].item_weight << std::endl;
    }
    std::cout << std::endl;
}



// public types
template<typename T>
struct Knapsack<T>::Item {
    public:
        int item_no;
        T item_value;
        T item_weight;
}


template<typename T>
class Knapsack<T>::Item_sort_by_item_no {
    public:
        bool operator()(const Knapsack<T>::Item &item1, const Knapsack<T>::Item &item2) {
            return item1.item_no < item2.item_no;
        }
};


template<typename T>
class Knapsack<T>::Item_sort_by_value {
    public:
        bool operator()(const Knapsack<T>::Item &item1, const Knapsack<T>::Item &item2) {
            return item1.item_value < item2.item_value;
        }
};


template<typename T>
class Knapsack<T>::Item_sort_by_weight {
    public:
        bool operator()(const Knapsack<T>::Item &item1, const Knapsack<T>::Item &item2) {
                return item1.item_weight < item2.item_weight;
        }
};



// declare dummy templates
template class Knapsack<int>;
template class Knapsack<long>;