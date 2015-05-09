#include <stddef.h>
#include "../DrzewaTest/gtest-1.7.0/include/gtest/internal/gtest-port.h"

//
// Created by Janusz Grzesik on 09.05.15.
//

using namespace std;
void replaceAll( string &s, const string &search, const string &replace ) {
    // Copyright: rotmax
    // from http://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

struct RedBlackNode{
    int key;
    RedBlackNode* parent;
    RedBlackNode* left;
    RedBlackNode* right;
    char color;

    RedBlackNode(int k, char c){
        // Constructor for non-leaf nodes
        key = k;
        color = c;
        parent = nullptr;
        right = new RedBlackNode();
        right->parent = this;
        left = new RedBlackNode();
        left->parent=this;
    }

    RedBlackNode(){
        // Constructor for leafs
        color = 'B';
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    bool is_leaf(){
        return (color=='B' && left == nullptr && right == nullptr);
    }
};


RedBlackNode* insert_BST_style(RedBlackNode* &root,int key_to_insert){
    // Creates a new node with the key value of key_to_insert
    // Inserts the node on first position that matches BST property
    // Returns a pointer to the inserted node

    if(root==nullptr){
        root=new RedBlackNode(key_to_insert,'B');
        return root;
    }
    RedBlackNode* current = root;
    while(!current->is_leaf()){
        if(current->key <= key_to_insert){
            current=current->right;
        }
        else{
            current=current->left;
        }
    }
    current->color='R';
    current->key= key_to_insert;
    current->right=new RedBlackNode();
    current->right->parent=current;
    current->left=new RedBlackNode();
    current->left->parent=current;
    return current;
}

string tree_to_string_with_tabs(RedBlackNode * root){
    // Returns a tree structured string that represents the RedBlackTree
    // All Black nodes are surrounded by "|"
    // All Red nodes are surrounded by "."
    // All leafs are printed as "_"
    if(root->is_leaf()){
        return "\n|_|";
    }
    string result=tree_to_string_with_tabs(root->right);
    replaceAll(result,"\n","\n\t");
    if(root->color=='B') {
        result += "\n|" + to_string(root->key)+"|";
    }else{
        result += "\n." + to_string(root->key)+".";
    }

    string result2=tree_to_string_with_tabs(root->left);
    replaceAll(result2,"\n","\n\t");
    result+=result2;
    return result;
}




void right_rotate(RedBlackNode* node_to_rotate, RedBlackNode* & root){
    if(node_to_rotate->left->is_leaf()){
        cout<<"WARNING ATTEMPTING TO PERFORM A RIGHT ROTATION WITHOUT LEFT SON"<<endl;
        return;
    }
    RedBlackNode* original_parent = node_to_rotate->parent;
    RedBlackNode* left_son = node_to_rotate->left;
    RedBlackNode* left_sons_right_son = node_to_rotate->left->right;

    if(original_parent!= nullptr){
        if(node_to_rotate==original_parent->right) {
            original_parent->right = left_son;
        }
        else{
            original_parent->left=left_son;
        }
    }
    left_son->parent = original_parent;
    left_son->right=node_to_rotate;
    node_to_rotate->parent=left_son;
    node_to_rotate->left=left_sons_right_son;
    left_sons_right_son->parent=node_to_rotate;
    if(original_parent== nullptr){
       root=left_son;
    }
}
void left_rotate(RedBlackNode* node_to_rotate,RedBlackNode* &root){
    if(node_to_rotate->right->is_leaf()){
        cout<<"WARNING ATTEMPTING TO PERFORM A LEFT ROTATION WITHOUT RIGHT SON"<<endl;
        return;
    }
    RedBlackNode* original_parent = node_to_rotate->parent;
    RedBlackNode* right_son = node_to_rotate->right;
    RedBlackNode* right_sons_left_son = node_to_rotate->right->left;

    if(original_parent!= nullptr){
        if(node_to_rotate==original_parent->right) {
            original_parent->right = right_son;
        }
        else{
            original_parent->left=right_son;
        }
    }
    right_son->parent = original_parent;
    right_son->left=node_to_rotate;
    node_to_rotate->parent=right_son;
    node_to_rotate->right=right_sons_left_son;
    right_sons_left_son->parent=node_to_rotate;
    if(original_parent== nullptr){
        root=right_son;
    }
}

RedBlackNode* find_by_key(RedBlackNode* root, int key_to_find){
    // Recursive function that attempts to find a node with key_to_find
    // If no Node has key_to_find a nullptr is returned
    // If more than one nodes have key_to_find the one closest to root is returned
    if(root== nullptr){
        return root;
    }
    if(root->is_leaf()){
        return nullptr;
    }
    if(root->key==key_to_find){
        return root;
    }
    if(root->key>key_to_find){
        return find_by_key(root->left, key_to_find);
    }
    return find_by_key(root->right, key_to_find);
}

void red_black_insert(RedBlackNode* &root, int key_to_insert){
    RedBlackNode* current = insert_BST_style(root, key_to_insert);
    RedBlackNode* temp;
    current->color='R';
    while(current!=root && current->parent->color=='R'){
        if(current->parent==current->parent->parent->left){
            temp = current->parent->parent->right;
            if(temp->color == 'R'){
                current->parent->color='B';
                temp->color='B';
                current->parent->parent->color='R';
                current=current->parent->parent;
            }
            else if(current==current->parent->right){
                current=current->parent;
                left_rotate(current,root);
            }
            else {
                current->parent->color = 'B';
                current->parent->parent->color = 'R';
                right_rotate(current->parent->parent, root);
            }
        }
        else{
            temp = current->parent->parent->left;
            if(temp->color == 'R'){
                current->parent->color='B';
                temp->color='B';
                current->parent->parent->color='R';
                current=current->parent->parent;
            }
            else if(current==current->parent->left){
                current=current->parent;
                right_rotate(current,root);
            }
            else {
                current->parent->color = 'B';
                current->parent->parent->color = 'R';
                left_rotate(current->parent->parent, root);
            }
        }
    }
    root->color='B';
}