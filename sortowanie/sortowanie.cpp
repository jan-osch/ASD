//
//  main.cpp
//  ASD
//
//  Created by Janusz Grzesik on 16.03.2015.
//  Copyright (c) 2015 Janusz Grzesik. All rights reserved.
//

#include <iostream>
using namespace std;

long parent(long index){
    return (index-1)/2;
}
long right(long index){
    return index*2+2;
}
long left(long index){
    return index*2+1;
}

void heapify( long *T, long n, long index){
    long maxIndex = index;
    
    if(right(index)<n && T[right(index)]>T[index]){
        maxIndex =right(index);
    }
    if(left(index)<n && T[left(index)]>T[maxIndex]){
        maxIndex =left(index);
    }
    
    if (maxIndex!=index){
        swap(T[maxIndex], T[index]);
        heapify(T, n, maxIndex);
    }
}

void buildHeap(long *T, long n){
    for(long i=parent(n-1); i>=0; i--){
        heapify(T,n, i);
    }
}

void heapSort(long *T, long n){
    buildHeap(T, n);
    for(long i=n-1; i>=0; i--){
        swap(T[i],T[0]);
        heapify(T,i,0);
    }
}

void insertionSort(long * T, long n){
    long key;
    long j;
    for(long i=1; i<n; i++){
        key=T[i];
        j=i-1;
        while(j>=0 && T[j]>key){
            T[j+1]=T[j];
            j--;
        }
        T[j+1]=key;
    }
}

long partition(long * T, long p, long n){
    /**
     Swaps elements in the list T so that 
     T[p] to T[pivot-1] are equal or less than T[pivot]
     T[pivot+1] to T[n-1] are greater than T[pivot]
     and returns pivot
     
     long *T    an array of long integers to be sorted
     long p     first index in the part to be sorted
     long n     first index NOT in the part to be sorted
     
     return    index of the pivot
     */
    
    
    long key = T[n-1];
    long head =p;
    long tail=p-1;
    while(head<n){
        if(T[head]<=key){
            tail++;
            swap(T[head],T[tail]);
        }
        head++;
    }
    return tail;
}

void countSort(long *T, long n, long k){
    /**
     Sorts the elements in T in growing order
     elements in T have to have values in the set {0,1,..,k-1}
     is stable
     
     long *T    an array of long integers to be sorted
     long n     length of the array to be sorted
     long k     maximum value of elements in T
     */
    
    long A[k];
    long Final[n];
    long index;
    
    for(long i=0; i<k; i++) A[i]=0;
    for(long i=0; i<n; i++) A[T[i]]++;
    for(long i=1; i<k; i++) A[i]+=A[i-1];
    for(long i=n-1; i>=0; i--) {
        index=A[ T[i] ]--;
        Final[index-1]=T[i];
    }
    for(long i=0; i<n; i++) T[i]=Final[i];
}

long reversePartition(long *T, long p, long n){
    long key = T[n-1];
    long head = p;
    long tail = p-1;
    while(head<n){
        if(T[head]>=key){
            tail++;
            swap(T[head],T[tail]);
        }
        head++;
    }
    return tail;
}

void quickSort(long *T, long p, long n){
    /**
    QuickSorts the array T
     
    long *T    an array of long integers to be sorted
    long p     first index in the part to be sorted
    long n     first index NOT in the part to be sorted
    */
    
    if(p>=n) return;
    
    long tail = partition(T,p,n);
    quickSort(T,p,tail);
    quickSort(T,tail+1, n);
}

long findKTH(long *T, long p, long n, long k){
    /**
     Finds the k-th number in a growing order in the list T
     
     long *T    an array of long integers to be investigated
     long p     first index in the part to be investigated
     long n     first index NOT in the part to be investigated
     */
    
    if ((n-p) <= 1) return T[p];
    
    long pivot = partition(T,p,n);
    if (pivot == k) return T[pivot];
    if (pivot<k) return findKTH(T, pivot+1, n, k);
    else return findKTH(T, p, pivot, k);
}

void selectionSort(long *T, long n){
    long minIndex;
    for(long i=0; i<n;i++){
        minIndex=i;
        for(long j=i+1; j<n; j++){
            if(T[j]<T[minIndex]){
                minIndex = j;
            }
        }
        swap(T[minIndex], T[i]);
    }
}

void merge(long * T, long s , long m, long f, long * B){
    long right=m;
    for(long final=s; final<=f;){
        if( s<m && right<f){
            
            if(T[s]<=T[right]){
                B[final]=T[s];
                s++;
            }
            else{
                B[final]=T[right];
                right++;
            }
            final++;
        }
        while(s==m && final<=f){
            B[final]=T[right];
            right++;
            final++;
        }
        while(right==f && final<=f){
            B[final]=T[s];
            s++;
            final++;
        }
    }
}
void mergeNatural(long *T, long n){
    /**
     long *T    an array of long integers to be sorted
     long n     length of the array or the first index NOT included ind array
     */
    
    long s=0;
    long m=0;
    long f=0;
    long * B = new long[n];
    
    
    while(s!=0 || m<n){ //outer loop
        s=f;
        m=s+1;
        while(m<n && T[m]>=T[m-1]){
            m++;
        }
        f=m+1;
        while(f<n && T[f]>=T[f-1]){
            f++;
        }
        if(f!=n+1){
            merge(T,s,m,f,B);
            for(long i=s; i<f; i++){
                T[i]=B[i];
            }
        }
        if(f>=n){
            f=0;
        }
    }
    delete[] B;
    
}

void mergeSort(long *T, long n){
    if(n<=1) return;
    long r = n/2;
    
    mergeSort(T, r);
    mergeSort(T+r,n-r);
    
    long * B = new long[n];
    merge(T,0,r,n,B);
    for(long i=0; i<n; i++) T[i]=B[i];
}

int main(int argc, const char * argv[]) {
    long arraySize;
    bool sorted=false;
    string sortingMethod;
    
    switch (argc){
        case 1:
            //sortingMethod="selectionSort";
            //sortingMethod="mergeSort";
            //sortingMethod="mergeNatural";
            //sortingMethod="quickSort";
            //sortingMethod="heapSort";
            sortingMethod="countSort";
            //sorted=true;
            arraySize=10;
            break;
        case 2:
            sortingMethod=argv[1];
            arraySize=100;
            break;
        case 3:
            sortingMethod=argv[1];
            arraySize=strtol(argv[2], NULL, 0);
            break;
        case 4:
            sortingMethod=argv[1];
            arraySize=strtol(argv[2], NULL, 0);
            sorted=true;
            break;
    }
    
    cout<<"Chosen Sorting method "<< sortingMethod<<endl;
    
    //Populate array with random numbers
    long * array = new long[arraySize];
    if(!sorted){
        for(long i=0; i<arraySize; i++){
            array[i]=rand() % arraySize;
            //cout<<" "<<array[i];
        }
    }else{
        for(long i=0; i<arraySize; i++){
            array[i]=i;
        }
    }
    //cout<<endl;
    
    //cout<<findKTH(array,0,arraySize, 6)<<endl;
    
    if(sortingMethod == "insertionSort"){
        insertionSort(array, arraySize);
    }
    if(sortingMethod == "selectionSort"){
        selectionSort(array, arraySize);
    }
    if(sortingMethod == "mergeSort"){
        mergeSort(array, arraySize);
    }
    if(sortingMethod == "mergeNatural"){
        mergeNatural(array, arraySize);
    }
    if(sortingMethod == "heapSort"){
        heapSort(array, arraySize);
    }
    if(sortingMethod == "quickSort"){
        quickSort(array,0, arraySize);
    }
    if(sortingMethod == "countSort"){
        countSort(array, arraySize, arraySize);
    }
    
    for(long i=1; i<arraySize; i++){
        if(array[i-1]>array[i]){
            cout<<"NOT SORTED"<<endl;
            break;
        }
    }
    //Check if first 10 and last 10 elements are printed in order
    for(long i=0; i<10; i++){
        cout<<" "<<array[i];
    }
    cout<<"...";
    for(long i=(arraySize-10); i < arraySize; i++){
        cout<<" "<<array[i];
    }
    cout<<endl;
    
    return 0;
}
