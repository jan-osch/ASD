//
// Created by Janusz Grzesik on 12.05.15.
//

#include <algorithm>
#include <iostream>

#ifndef ASD_AVL_TREES_H
#define ASD_AVL_TREES_H

#endif //ASD_AVL_TREES_H

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

struct AVLNode{
    int key;
    int height;
    int balance;
    AVLNode* parent;
    AVLNode* right;
    AVLNode* left;

    AVLNode(int k){
        parent= nullptr;
        right= nullptr;
        left= nullptr;
        key = k;
        balance= 0;
        height=0;
    }
};

void compute_height(AVLNode* node){
    int left;
    int right;
    if(node->left== nullptr){
        left=-1;
    }else{
        left=node->left->height;
    }
    if(node->right== nullptr){
        right=-1;
    }else{
        right=node->right->height;
    }
    node->height=std::max(left, right)+1;
    node->balance=right-left;
}

AVLNode* insert_key(AVLNode* &root, int key_to_insert){
    // Inserts new node to the tree and returns a pointer to the new node
    // If root is a nullptr then it will be modified
    if(root== nullptr){
        root=new AVLNode(key_to_insert);
        return root;
    }
    AVLNode* result;
    if(root->key>key_to_insert){
        result = insert_key(root->left, key_to_insert);
        root->left->parent=root;
        return result;
    }
    result = insert_key(root->right, key_to_insert);
    root->right->parent=root;
    return result;
}

void right_rotate(AVLNode* node_to_rotate, AVLNode* & root) {
    if (node_to_rotate->left == nullptr) {
        std::cout << "WARNING ATTEMPTING TO PERFORM A RIGHT ROTATION WITHOUT LEFT SON" << std::endl;
        return;
    }
    AVLNode *original_parent = node_to_rotate->parent;
    AVLNode *left_son = node_to_rotate->left;
    AVLNode *left_sons_right_son = node_to_rotate->left->right;

    if (original_parent != nullptr) {
        if (node_to_rotate == original_parent->right) {
            original_parent->right = left_son;
        }
        else {
            original_parent->left = left_son;
        }
    }
    left_son->parent = original_parent;
    left_son->right = node_to_rotate;
    node_to_rotate->parent = left_son;
    node_to_rotate->left = left_sons_right_son;
    if (left_sons_right_son != nullptr) {
        left_sons_right_son->parent = node_to_rotate;
    }
    if(original_parent== nullptr){
        root=left_son;
    }
}
void left_rotate(AVLNode* node_to_rotate,AVLNode* &root){
    if(node_to_rotate->right== nullptr){
        std::cout<<"WARNING ATTEMPTING TO PERFORM A LEFT ROTATION WITHOUT RIGHT SON"<<std::endl;
        return;
    }
    AVLNode* original_parent = node_to_rotate->parent;
    AVLNode* right_son = node_to_rotate->right;
    AVLNode* right_sons_left_son = node_to_rotate->right->left;

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
    if(right_sons_left_son!= nullptr) {
        right_sons_left_son->parent = node_to_rotate;
    }
    if(original_parent== nullptr){
        root=right_son;
    }
}


void AVL_insert(AVLNode* &root, int key_to_insert){
    // Uses insert_key to insert the new key in regular BST way
    // Then inspects and repairs the AVL properties until it returns to root

    AVLNode * tail = insert_key(root, key_to_insert);
    AVLNode * head = tail->parent;
    AVLNode * temp;
    while(head!= nullptr){
        compute_height(head);
        if(head->balance==2){
            if(tail->balance>-1){
                left_rotate(head,root);
                compute_height(head);
                compute_height(tail);
                temp = head;
                head = tail;
                tail = temp;
            }else{
                right_rotate(tail, root);
                compute_height(tail);
                tail=tail->parent;
                compute_height(tail);
                left_rotate(head,root);
                compute_height(head);
                compute_height(tail);
                temp = head;
                head = tail;
                tail = temp;
            }
        }
        else if(head->balance==-2){
            if(tail->balance<1){
                right_rotate(head,root);
                compute_height(head);
                compute_height(tail);
                temp = head;
                head = tail;
                tail = temp;
            }else{
                left_rotate(tail, root);
                compute_height(tail);
                tail=tail->parent;
                compute_height(tail);
                right_rotate(head,root);
                compute_height(head);
                compute_height(tail);
                temp = head;
                head = tail;
                tail = temp;
            }
        }
        head=head->parent;
        tail=tail->parent;
    }
}

string avl_tree_to_string(AVLNode * root){
    // Returns a tab and newline structured string that represents the AVLTree
    // The balance values are printed after "|"
    // Right subtree is printed higher than root ant with one tab indent
    // Left subtree is printed lower than root and with one tab indent

    if(root== nullptr){
        return "";
    }
    string result=avl_tree_to_string(root->right);
    replaceAll(result,"\n","\n\t");
    result +="\n"+to_string(root->key)+"|"+to_string(root->balance);

    string result2=avl_tree_to_string(root->left);
    replaceAll(result2,"\n","\n\t");
    result+=result2;
    return result;
}
