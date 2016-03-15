#ifndef _KNAPSACK_H
#define _KNAPSACK_H

#include <map>
#include <vector>

template<typename T>
class Knapsack {
    public:
        Knapsack(const std::map<T, std::vector<T> > &items, T sack_size);
        ~Knapsack();
        T get_solution();
        void test();
        
    public:
        struct Item;
        class Item_sort_by_item_no;
        class Item_sort_by_value;
        class Item_sort_by_weight;
         
    private:
        const int NUM_ITEMS, SACK_SIZE;
        bool solution_complete;
        T max_weight, solution;
        Item *item_list;
        
    private:
        void solve();

    private:   
        // make copying illegal
        Knapsack(const Knapsack<T> &knapsack_object) : NUM_ITEMS(1), SACK_SIZE(1) {}
        Knapsack &operator=(const Knapsack<T> &knapsack_object) { return (*this); }
};

#endif