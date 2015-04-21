#include <stack>
using namespace std;

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

bool isLeaf(node* node){
    if(node->right==nullptr && node->left==nullptr){
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

int findMin(node* root){
    /* This method should not be called 
     * on an empty tree
     */
    if(root == nullptr){
        cout<<"Invalid Argument - Method should not be called on an emtpy tree"<<endl;
        return -1;
    }
    while(root->left!=nullptr){
        root=root->left;
    }
    return root->key;
}

int findMax(node* root){
    /* This method should not be called
     * on an empty tree
     */
    if(root == nullptr){
        cout<<"Invalid Argument - Method should not be called on an emtpy tree"<<endl;
        return -1;
    }
    while(root->right!=nullptr){
        root=root->right;
    }
    return root->key;
}

node* findSuccessor(node *root){
    if(root == nullptr){
        return root;
    }
    if(root->right!=nullptr){
        return root->right;
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
        return root->left;
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
