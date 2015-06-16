//
// Created by Janusz Grzesik on 15.06.15.
//

#ifndef ASD_LCS_FINDER_H
#define ASD_LCS_FINDER_H

#include <string>
#include <vector>


using namespace std;

vector<vector<int> > create_lcs_table(char* string1, char* string2, int len1, int len2){

    vector<vector<int> >result (len1+1, vector<int>(len2+1,0));
    for(int i=0; i<=len1; i++){
        for(int j=0; j<=len2; j++){
            if(i==0 || j==0){}
            else if(string1[i-1] == string2[j-1]){
                result[i][j]=result[i-1][j-1]+1;
            }
            else{
                result[i][j]=max(result[i-1][j], result[i][j-1]);
            }
        }
    }
    return result;
}
string lcs_find(char* string1, char* string2, int position1, int position2, vector<vector<int> > lcs_table){
    if(lcs_table[position1][position2]==0){
        return "";
    }
    if(string1[position1-1]==string2[position2-1]){
        return lcs_find(string1, string2, position1-1, position2-1, lcs_table) + string1[position1-1];
    }
    if(lcs_table[position1-1][position2]>=lcs_table[position1][position2-1]){
        return lcs_find(string1, string2, position1-1, position2, lcs_table);
    }
    return lcs_find(string1, string2, position1, position2-1, lcs_table);
}

string LCS_finder(char* string1, char* string2, int len1, int len2){
    vector<vector<int> > lcs_table = create_lcs_table(string1, string2, len1, len2);
    return lcs_find(string1, string2, len1, len2, lcs_table);
}
#endif //ASD_LCS_FINDER_H
