//
// Created by Janusz Grzesik on 16.06.15.
//

#ifndef ASD_SWAPING_STRINGS_H
#define ASD_SWAPING_STRINGS_H

#include <vector>
#include "iostream"
using namespace std;

void create_swap_tables(char* string1, char* string2, int len1, int len2, vector<vector<int> > &cost, vector<vector<char> > &operation){
    for(int i=0; i<=len1; i++){
        for(int j=0; j<=len2; j++){
            if(i==0 && j==0){
                cost[i][j]=0;
                operation[i][j]='_';
            }
            else if(i==0){
                cost[i][j]=j*2;
                operation[i][j]='I';
            }
            else if(j==0){
                cost[i][j]=i*2;
                operation[i][j]='D';
            }
            else{
                if (string1[i - 1] == string2[j - 1]) {
                    cost[i][j] = cost[i - 1][j - 1] - 1;
                    operation[i][j] = 'K';
                }
                else{
                    cost[i][j]=cost[i-1][j-1]+1;
                    operation[i][j]='R';
                }
                if(cost[i][j-1]+2<cost[i][j]){
                    cost[i][j]=cost[i][j-1]+2;
                    operation[i][j]='I';
                }
                if(cost[i-1][j]+2<cost[i][j]){
                    cost[i][j]=cost[i-1][j]+2;
                    operation[i][j]='D';
                }
            }
        }
    }
}

string find_swapping_results(char* string1, char* string2, int len1, int len2, vector<vector<int> > cost, vector<vector<char> > operation){
    if(len2==0){
        return "";
    }
    if(operation[len1][len2]=='D'){
        cout<<"Delete "<<string1[len1-1]<<" at position "<<len1-1<<endl;
        return find_swapping_results(string1, string2, len1-1, len2, cost, operation);
    }
    if(operation[len1][len2]=='I'){
        cout<<"Insert "<<string2[len2-1]<<" at position "<<len1-1<<endl;
        return find_swapping_results(string1, string2, len1, len2-1, cost, operation)+string2[len2-1];
    }
    if(operation[len1][len2]=='R'){
        cout<<"Replace "<<string1[len1-1]<<" at position "<<len1-1<<" with "<<string2[len2-1]<<endl;
        return find_swapping_results(string1, string2, len1, len2-1, cost, operation)+string2[len2-1];
    }
    cout<<"Copy "<<string1[len1-1]<<" at position "<<len1-1<<" to "<<string2[len2-1]<<endl;
    return find_swapping_results(string1, string2, len1-1, len2-1, cost, operation)+string2[len2-1];
}

string swap_two_strings(char* string1, char* string2, int len1, int len2){
    vector<vector<int> > costs(len1+1, vector<int>(len2+1,0));
    vector<vector<char> > operation(len1+1, vector<char>(len2+1, '_'));
    create_swap_tables(string1, string2, len1, len2, costs, operation);
    cout<<"Summaric cost: " <<costs[len1][len2]<<endl;
    return find_swapping_results(string1, string2, len1, len2, costs, operation);
}



#endif //ASD_SWAPING_STRINGS_H
