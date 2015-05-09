//
// Created by Janusz Grzesik on 08.05.15.
//
#include "iostream"
#include "tablice_haszujace.h"
using namespace std;

int main(int argc, const char * argv[]) {
    HashTable<int>* ht = new HashTable<int>(11);
//    int o = 5;
//    int t = 8;

//    insertion_double(*ht,2,hash_function_one, hash_function_two);

    insertion_linear(*ht, 2, hash_function_one);
    insertion_linear(*ht, 2, hash_function_one);
    insertion_linear(*ht, 7, hash_function_one);
    insertion_linear(*ht, 3, hash_function_one);
    remove_linear(*ht, 2, hash_function_one);
    remove_linear(*ht, 2, hash_function_one);
    remove_linear(*ht, 3, hash_function_one);
    remove_linear(*ht, 3, hash_function_one);
    ht->print_hash_table();
    return 0;
}