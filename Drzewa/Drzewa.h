#include <iostream>
#include <stack>
#define MIN_VAL -10000000
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

struct node{
    
    node* parent;
    node* left;
    node* right;
    int key;
    
    node(int val){
        key=val;
        left=nullptr;
        right=nullptr;
        parent=nullptr;
    }

    virtual ~node() { }
};

node* insert(node* root,int val){
    /* Creates a new node in the tree
     * If a node with the same key exist
     * The new node will be added as right son
     */
    if(root==nullptr){
        root= new node(val);
    }
    else if(root->key>val){
        root->left=insert(root->left, val);
        root->left->parent=root;
    }else{
        root->right=insert(root->right, val);
        root->right->parent=root;
    }
    return root;
}

node* treeBuilder(int * arrayOfInts, int n){
    node* root=nullptr;
    for ( int i =0; i < n; i++){
        root=insert(root, arrayOfInts[i]);
    }
    return root;
}

bool isLeaf(node* node_to_test){
    if(node_to_test->right==nullptr && node_to_test->left==nullptr){
        return true;
    }
    return false;
}

string printInOrder(node * root){
    string result;
    stack<node *> myStack;
    myStack.push(root);
    node * currentNode;
    node * tempNode;
    
    while(!myStack.empty()){
        currentNode = myStack.top();
        myStack.pop();
        if(currentNode==nullptr){
            continue;
        }
        if(isLeaf(currentNode)){
            result=result+to_string(currentNode->key)+"\n";
            continue;
        }
        if(!myStack.empty()){
            tempNode = myStack.top();
            if(tempNode == currentNode){
                result=result+to_string(currentNode->key)+"\n";
                myStack.pop();
                continue;
            }
        }
        myStack.push(currentNode->right);
        myStack.push(currentNode);
        myStack.push(currentNode);
        myStack.push(currentNode->left);
    }
    return result;
}

string printInOrderRecursively(node * root){
    if(root==nullptr){
        return "";
    }
    string result=printInOrderRecursively(root->left);
    result+=to_string(root->key)+"\n";
    result+=printInOrderRecursively(root->right);
    return result;
}


string tree_to_string_with_tabs(node * root){
    if(root==nullptr){
        return "";
    }
    string result=tree_to_string_with_tabs(root->right);
    replaceAll(result,"\n","\n\t");
    result+="\n"+to_string(root->key);
    string result2=tree_to_string_with_tabs(root->left);
    replaceAll(result2,"\n","\n\t");
    result+=result2;
    return result;
}

string printInOrderOnStack(node * root){
    string result;
    stack<node *> myStack;
    myStack.push(root->left);
    node * currentNode;
    
    while(!myStack.empty()){
        currentNode = myStack.top();
        myStack.pop();
        if(currentNode==nullptr){
            continue;
        }
        if(isLeaf(currentNode)){
            result=result+to_string(currentNode->key)+"\n";
            continue;
        }
    }
    return result;
}

node* find_node_by_key(node* root, int key_to_find){
    // Attempts to find the first node with given key
    // If the given key is found a pointer to the node is returned
    // If the key is not present in the tree a nullptr is returned
    if(root == nullptr || root->key==key_to_find){
        return root;
    }
    if(root->key<key_to_find){
        return find_node_by_key(root->right, key_to_find);
    }
    return find_node_by_key(root->left, key_to_find);
}

int findMin(node* root){
    // This function should not be called on an empty tree
    // If findMin is called on an empty tree a warning is printed to std::out
    // and a value of macro MIN_VAL is returned
    if(root == nullptr){
        cout<<"Invalid Argument - Method should not be called on an emtpy tree"<<endl;
        return MIN_VAL;
    }
    while(root->left!=nullptr){
        root=root->left;
    }
    return root->key;
}

int findMax(node* root){
    // This function should not be called on an empty tree
    // If findMax is called on an empty tree a warning is printed to std::out
    // and a value of macro MIN_VAL is returned
    if(root == nullptr){
        cout<<"Invalid Argument - Method should not be called on an emtpy tree"<<endl;
        return -1;
    }
    while(root->right!=nullptr){
        root=root->right;
    }
    return root->key;
}

node* find_max_node(node* root){
    // Attempts to find the node that has the maximum key in subtree of root
    // if root is empty a nullptr is returned
    if(root == nullptr || isLeaf(root)){
        return root;
    }
    while(root->right!=nullptr){
        root=root->right;
    }
    return root;
}

node* find_min_node(node* root){
    // Attempts to find the node that has the minimum key in subtree of root
    // if root is empty a nullptr is returned
    if(root == nullptr || isLeaf(root)){
        return root;
    }
    while(root->left!=nullptr){
        root=root->left;
    }
    return root;
}

node* findSuccessor(node *root){
    if(root == nullptr){
        return root;
    }
    if(root->right!=nullptr){
        return find_min_node(root->right);
    }
    node* previous;
    while(root->parent!=nullptr){
        previous = root;
        root = root->parent;
        if(previous==root->left){
            return root;
        }
    }
    return nullptr;
}

node* findPredecessor(node *root){
    if(root == nullptr){
        return root;
    }
    if(root->left!=nullptr){
        return find_max_node(root->left);
    }
    node* previous;
    while(root->parent!=nullptr){
        previous = root;
        root = root->parent;
        if(previous==root->right){
            return root;
        }
    }
    return nullptr;
}

bool remove_from_tree(node* &root, node* node_to_remove){
    // This function attempts to remove give node from the tree
    // The node_to_remove has to exist in the tree
    // The tree root may be modified

    // node_to_remove is a leaf
    if( isLeaf(node_to_remove)){
        if(node_to_remove->parent!= nullptr){
            if(node_to_remove->parent->right==node_to_remove){
                node_to_remove->parent->right= nullptr;
            }
            else{
                node_to_remove->parent->left= nullptr;
            }
        }
        else{
            root = nullptr;
        }
        return true;
    }

    // node_to_remove has a single son
    if(node_to_remove->left== nullptr || node_to_remove->right==nullptr){


        // modify sons parent reference
        if(node_to_remove->left== nullptr){
            node_to_remove->right->parent=node_to_remove->parent;
        }
        else{
            node_to_remove->left->parent=node_to_remove->parent;
        }

        // node_to_remove is not root
        if(node_to_remove->parent!= nullptr){
            if(node_to_remove->parent->right==node_to_remove){
                node_to_remove->parent->right= node_to_remove->right== nullptr
                                               ? node_to_remove->left : node_to_remove->right;
            }
            else{
                node_to_remove->parent->left= node_to_remove->right== nullptr
                                              ? node_to_remove->left : node_to_remove->right;
            }
        }
        else{
            root = node_to_remove->left== nullptr ? node_to_remove->right : node_to_remove->left;
        }
        return true;
    }


    //node_to_remove has two sons
    node * successor = findSuccessor(node_to_remove);

    while(successor->left!= nullptr && successor->right!= nullptr){
        successor = findSuccessor(successor);
    }
    remove_from_tree(root, successor);

    if(node_to_remove->parent!= nullptr){
        if(node_to_remove->parent->right==node_to_remove){
            node_to_remove->parent->right=successor;
        }else{
            node_to_remove->parent->left=successor;
        }
    }
    else{
        root = successor;
    }
    successor->parent= node_to_remove->parent;
    successor->right = node_to_remove->right;
    if(successor->right != nullptr){
        successor->right->parent = successor;
    }
    successor->left=node_to_remove->left;
    if(successor->left != nullptr){
        successor->left->parent = successor;
    }
    return true;
}

