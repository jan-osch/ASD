//
//  main.cpp
//  QuickerSort
//
//  Created by Janusz Grzesik on 29.03.2015.
//  Copyright (c) 2015 Janusz Grzesik. All rights reserved.
//

#include <iostream>
using namespace std;

struct node {
    node * next;
    long value;
};
/*
void swapNextOnes (node * previous1, node * previous2){
    // Swaps two elements in a one-directional list
    // Arguments are two elements that are prior
    // in the list to the elements that are going to be swapped
    
    node * actual1 = previous1 -> next;
    node * after1 = actual1 -> next;
    
    node * actual2 = previous2 -> next;
    node * after2 = actual2 -> next;
    
    cout<< "HEJA";
    
    previous2 -> next = actual1;
    previous1 -> next = actual2;
    
    actual2 -> next = after1;
    actual1 -> next = after2;
    
}

void swapFirst (node * & original, node * previous2){
    // Swaps two elements in a one-directional list
    // original is the first element in the list
    
    
    node * copy = original;
    node * after1 = copy -> next;
    
    node * actual2 = previous2 -> next;
    node * after2 = actual2 -> next;
    
    copy -> next = after2;
    actual2 -> next = after1;
    previous2 -> next = copy;
    original = actual2;
}

void quickerPartition2 (node * & original, node * & first, node * & last){
    // Partition function for quickerSort
    // Chooses first element in the list as key
    // Divides a one-directional list into 3 groups:
    // Group1 - smaller than key
    // Group2 - equal to key
    // Group3 - greater than key
    //
    // Arguments before:
    // original - head of the list
    // first - null
    // last - null
    //
    // Arguments after:
    // original - head of the list
    // first - first element of Group2
    // last -last element of Group2
    
    node * head = original;
    last = head;
    int key = head->value;
    
    while( head -> next != NULL){
        if( head -> next -> value == key){
            swapNextOnes(last, head);
            last = last -> next;
        }
        
        if( head -> next -> value < key){
            if( first == NULL){
                swapFirst(original, head);
            }
            else {
                swapNextOnes(first, head);
            }
            swapNextOnes(last, head);
            first = first -> next;
            last = last -> next;
        }
        head=head->next;
    }
    first=first->next;
}
*/
void quickerPartition (node *& firstHead, node *& secondHead, node *& thirdHead){
    
    node * tail = firstHead;
    node * firstTail = NULL;
    secondHead = firstHead;
    node * secondTail = firstHead;
    firstHead = NULL;
    node * thirdTail = NULL;
    long key = tail -> value;
    
    while (tail -> next != NULL){
        if ( tail -> next -> value > key){
            if (thirdTail == NULL){
                thirdHead = tail -> next;
                thirdTail = thirdHead;
            } else {
                thirdTail -> next = tail -> next;
                thirdTail = thirdTail -> next;
            }
        } else if ( tail -> next -> value == key){
            secondTail -> next = tail -> next;
            secondTail = secondTail -> next;
        } else  if ( tail -> next -> value < key) {
            if (firstTail == NULL){
                firstHead = tail -> next;
                firstTail = firstHead;
            } else {
                firstTail -> next = tail -> next;
                firstTail = firstTail -> next;
            }
        }
        tail = tail -> next;
    }
    if (firstTail != NULL){
        firstTail -> next = NULL;
    }
    secondTail -> next = NULL;
    if (thirdTail != NULL){
        thirdTail -> next = NULL;
    }
}


node * quickerSort ( node * head){
    // A QuickerSort algorithm
    // returns head to sorted one-directional list
    
    // Recursion limits:
    // The list should be at least two elements long
    
    if( head == NULL) return head;
    if( head -> next == NULL) return head;
    
    node * secondHead = NULL;
    node * thirdHead= NULL;
    quickerPartition(head, secondHead, thirdHead);
    
    thirdHead = quickerSort(thirdHead);
    head = quickerSort(head);
    
    node * tail = head;
    
    //Connect three lists into one
    if( tail == NULL){
        tail = secondHead;
        head = secondHead;
    }else{
        while(tail -> next != NULL){
            tail = tail -> next;
        }
        tail -> next  =  secondHead;
    }
    while( tail -> next != NULL){
        tail = tail -> next;
    }
    tail -> next = thirdHead;
    return head;
}

node * listBuilder( long * array, long length){
    // Builds a one-directional list from an array
    node * head = new node;
    head -> value = array[0];
    
    node * tail = head;
    node * current;
    for(long i = 1; i<length; i++){
        current = new node;
        current -> value = array[i];
        current -> next = NULL;
        
        tail -> next = current;
        tail = tail -> next;
    }
    return head;
}

void displayList(node * head){
    // Prints a one-directional list
    while (head != NULL){
        cout<<" "<< head->value;
        head =head ->next;
    }
    cout<< endl;
}

void checkLIst(node * head){
    // Checks if a one-directional list is sorted
    node * tail = head -> next;
    while (tail != NULL){
        if(tail -> value < head -> value){
            cout<< "WARNING NOT SORTED!"<< endl;
            return;
        }
        tail = tail -> next;
        head = head -> next;
    }
}

int main(int argc, const char * argv[]) {
    /*
    int array[] = {3,2,1,2,1, 3,5, 11, 12, 7};
    node * myList = listBuilder(array, 10);
    //int array[] = {3,2};
    
    //node * myList = listBuilder(array, 2);
    displayList(myList);
    
    
    node * secondHead = NULL;
    node * thirdHead = NULL;
    
    quickerPartition(myList, secondHead, thirdHead);
    displayList(myList);
    displayList(secondHead);
    displayList(thirdHead);
    
    myList = quickerSort(myList);
    displayList(myList);
    */
    long arraySize = arraySize=strtol(argv[1], NULL, 0);
    
    long * myArray = new long[arraySize];
    for(long i=0; i<arraySize; i++){
        myArray[i]=rand() % arraySize;
    }
    
    node * myList = listBuilder(myArray, arraySize);
    myList = quickerSort(myList);
    checkLIst(myList);
    
    return 0;
    
}
