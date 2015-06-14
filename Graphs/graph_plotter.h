//
// Created by Janusz Grzesik on 08.06.15.
//

#ifndef ASD_GRAPH_PLOTTER_H
#define ASD_GRAPH_PLOTTER_H

string printer_matrix_from_matrix(vector<vector<int> > input){
    string result = "";
    for(int i=0; i<input.size(); i++){
        for(int j=0; j<input.size(); j++){
            result+= to_string(input[i][j])+" ";
        }
    }
    return result;
}

string create_labels(vector<string> input){
    string result = "";
    for(int i=0; i<input.size(); i++){
        result+= input[i]+" ";
    }
    return result;
}

string create_highlight(vector<vector<bool> > input){
    string result = "";
    for(int i=0; i<input.size(); i++){
        for(int j=0; j<input.size(); j++) {
            if (input[i][j]) {
                result += "+ ";
            }else{
                result +="- ";
            }
        }
    }
    return result;
}

void plot_graph(int len, string matrix, bool directional, bool weighted, string labels, string highlights){
    string input = "~/Dysk\\ Google/ASD/ASD/Graph_Printer/printer.py";
    if(weighted){
        input+=" -w";
    }
    if(directional){
        input+=" -d";
    }
    if(labels!=""){
        input +=" -l \'"+labels+"\'";
    }
    if(highlights!=""){
        input +=" -j \'"+highlights+"\'";
    }
    input+=" "+to_string(len);
    input+=" \'"+matrix+"\'";
//    std:cout<<input<<endl;
    system(input.c_str());
    input = "open .";
    system(input.c_str());
}

#endif //ASD_GRAPH_PLOTTER_H
