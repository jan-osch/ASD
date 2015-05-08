//
// Created by Janusz Grzesik on 08.05.15.
//

#include "tablice_haszujace.h"
int main(int argc, const char * argv[]) {
    HashTable<int>* ht = new HashTable<int>(11);
    int o = 5;
    int t = 8;
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    insertion_double(*ht,2,hash_function_one, hash_function_two);
    ht->print_hash_table();

    return 0;
}