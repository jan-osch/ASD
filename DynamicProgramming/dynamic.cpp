//
// Created by Janusz Grzesik on 15.06.15.
//

#include <iostream>
#include "LCS_finder.h"
#include "swaping_strings.h"


using namespace std;

int main(int argc, const char * argv[]) {
    srand (time(NULL));
//    char * string1 = (char *)("lody_na_patyku prosze ja ciebie helenko i co my z tym zrobimy nie wiem za bardzoe");
//    char * string2 = (char *)("ala_ma_kotka a co na to twoja matka krzysztofku i wogole idziemy obierac kartofle");
//    int len1 = 81;
//    int len2 = 81;
//
//    cout<<LCS_finder(string1,string2, len1, len2);


    char * string1 = (char *)("GAT");
    char * string2 = (char *)("CAGT");
    int len1 = 3;
    int len2 = 4;
    cout<<swap_two_strings(string1,string2, len1, len2);
    return 0;

}