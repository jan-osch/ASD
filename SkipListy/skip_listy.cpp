//
// Created by Janusz Grzesik on 07.05.15.
//

#include <iostream>
#include "skip_listy.h"
using namespace std;

int main(int argc, const char * argv[]){
    srand (time(NULL));
    SkipList* listka = new SkipList();

    insert(*listka, 1);
    insert(*listka, 7);
    insert(*listka, 3);
    insert(*listka, 5);
    insert(*listka, 2);
    insert(*listka, 4);
    printSkipList( * listka);
    SLNode* result = find(* listka, 7);
    cout<< (result== nullptr)<<endl;
    cout<<  result->level;

    return 0;
}