//
// Created by Janusz Grzesik on 08.05.15.
//
#include <iostream>

template <class TYPE>
struct HashTableNodeOpenAddressing{
    HashTableNodeOpenAddressing(TYPE *data) : data(data) {
        deleted = false;
    }
    HashTableNodeOpenAddressing(){
        data = nullptr;
        deleted = false;
    }
    TYPE* data;
    bool deleted;

    TYPE get_data(){
        return *data;
    }

    ~HashTableNodeOpenAddressing() {
        delete data;
        deleted = false;
    }
};

template <class TYPE>
class HashTable{
public:
    HashTable(int size) : size(size) {
        table = new HashTableNodeOpenAddressing<TYPE>[size];
        number_of_elements = 0;
    }

    int size;
    int number_of_elements;
    HashTableNodeOpenAddressing<TYPE>*  table;
    double load_factor;

    void compute_load_factor(){
        load_factor = number_of_elements *1.0 / size;
    }
    void delete_if_pointer(TYPE* &t){
        delete t;
        t = nullptr;
    }
    void delete_if_pointer(TYPE t){};

    void print_hash_table(){
        for(int i = 0 ; i<this->size; i++){
            if(this->table[i].data == nullptr){
                std::cout<<"_"<<std::endl;
            }
            else{
                std::cout<< *(this->table[i].data)<<std::endl;
            }
        }
    }

};

template <class TYPE>
bool insert_at_index(HashTable<TYPE> hashTable, TYPE new_data, int index){
    //This function inserts the data at given index
    //If tha HashTable at the given index already has an item it will return false
    if(hashTable.table[index].data != nullptr){
        return false;
    }
    hashTable.table[index].data = new TYPE(new_data);
    hashTable.number_of_elements++;
    hashTable.compute_load_factor();
    return true;
}
template <class TYPE>
bool remove_at_index(HashTable<TYPE> hashTable,TYPE data_to_remove, int index){
    //This function removes the node at given index
    //If tha HashTable at the given index already has an item it will return false
    if(hashTable.table[index].data== nullptr || *(hashTable.table[index].data) != data_to_remove){
        return false;
    }
    hashTable.delete_if_pointer(hashTable.table[index].data);
    hashTable.table[index].deleted=true;
    hashTable.number_of_elements--;
    hashTable.compute_load_factor();
    return true;
}

template <class TYPE>
int hash_function_one(int size, TYPE data){
    return data % size;
}

template <class TYPE>
int hash_function_two(int size, TYPE data){
    return 1+ (data % (size-2));
}


template <class TYPE>
bool insertion_linear(HashTable<TYPE> hashTable, TYPE data, int (*f)(int ,TYPE)){
    if(hashTable.load_factor==1.0){
        return false;
    }
    int index = f(hashTable.size, data);
    for(int i= 0; i< hashTable.size; i++){
        if(insert_at_index(hashTable,data,(index + i)%hashTable.size)){
            return true;
        }
    }
    return false;
}

template <class TYPE>
bool remove_linear(HashTable<TYPE> hashTable, TYPE data_to_remove, int (*f)(int ,TYPE)){
    if(hashTable.load_factor==1.0){
        return false;
    }
    int index = f(hashTable.size, data_to_remove);
    for(int i= 0; i< hashTable.size; i++){
        if(remove_at_index(hashTable,data_to_remove,(index + i)%hashTable.size)){
            return true;
        }
    }
    return false;
}

template <class TYPE>
bool insertion_square(HashTable<TYPE> hashTable, TYPE data,int constant_one,int constant_two, int (*f)(int ,TYPE)){
    if(hashTable.load_factor==1.0){
        return false;
    }
    int index = f(hashTable.size, data);
    for(int i= 0; i< hashTable.size; i++){
        if(insert_at_index(hashTable,data,(index + constant_one * i + constant_two * i * i)%hashTable.size)){
            return true;
        }
    }
    return false;
}

template <class TYPE>
bool insertion_double(HashTable<TYPE> hashTable, TYPE data, int (*f)(int ,TYPE), int (*g)(int ,TYPE)){
    if(hashTable.load_factor==1.0){
        return false;
    }
    int index = f(hashTable.size, data);
    int second = g(hashTable.size, data);
    for(int i= 0; i< hashTable.size; i++){
        if(insert_at_index(hashTable,data,(index + i * second )%hashTable.size)){
            return true;
        }
    }
    return false;
}