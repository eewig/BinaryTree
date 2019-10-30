#include <iostream>
#include <string>

using namespace std;
#define COUNT 10 //for func print2DTree


struct Tree{
    int data;
    Tree* left;
    Tree* right;
    Tree* parent;
};

struct Tree* newTreeNode(int data);
struct Tree* insertTreeNode(Tree* node, int data);
Tree* getNode(Tree* node, int key);
void delNode(Tree* node, int key);
void printTree(Tree *p, int level);
void print2DTree(Tree* root, int space);


int main(){

    Tree* root = newTreeNode(22);
    insertTreeNode(root, 1);
    insertTreeNode(root, 2);
    insertTreeNode(root, 53);
    insertTreeNode(root, 19);
    print2DTree(root, 0);
    Tree* tNode;
    delNode(root, 2);
    print2DTree(root, 0);
    return 0;

}

struct Tree* newTreeNode(int data){
    Tree* root = new Tree();
    root->data.number = data.number;
    root->data.name = data.name;
    root->data.title = data.title;
    root->data.year = data.year;
    root->data.amount = data.amount;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;

    return root;
}

struct Tree* insertTreeNode(Tree* node, int data){
    static Tree* p;
    Tree* retNode;

    if(node == NULL){
        retNode = newTreeNode(data);
        retNode->parent = p;
        return retNode;
    }
    if(data.number<=node->data.number){
        p=node;
        node->left = insertTreeNode(node->left, data);
    }
    else{
        p=node;
        node-> right =insertTreeNode(node->right, data);
    }
    return node;
}

Tree* getNode(Tree* node, int key){
    if(node == NULL) return node;

    if(node->data.number == key) return node;
    else{
        if(node->data.number < key)
            return getNode(node->right, key);
        else
            return getNode(node->left, key);
        
    }
}


int treeMax(Tree* node){
    while(node->right){
        node = node->right;
    }
    return node->data.number;
}

int predecessorInOrder(Tree* node){
    if(node->left)
        return treeMax(node->left);
    Tree* t = node->parent;
    while(node == t->left){
        node = t;
        t = t->parent;
    }
    return t->data.number;
}

void delNode(Tree* root, int key){
    Tree *node, *p, *child, *pred;
    
    node = getNode(root, key);

    if(node->left == NULL && node->right == NULL){
        if(node->parent) p = node->parent;
        if(node == p->left)
            p->left = NULL;
        else 
            p->right = NULL;
        delete node;
        return;
    }
   if(node->left && node->right){
        int key_pred = predecessorInOrder(node);
        pred = getNode(root, key_pred);
        if(pred->parent->left == pred)
            pred->parent->left = NULL;
        else if(pred->parent->right == pred)
            pred->parent->right = NULL;
        node->data = pred->data;
        delete pred;
        return;
    }
    if(node->left)
        child = node->left;
    else if(node->right)
        child = node->right;
    p = node->parent;
    if(p->left && p->left == node){
        p->left = child;
    }
    else if(p->right && p->right == node){
        p->right = child;
    }
    child->parent = p;
    delete node;
    return;

}

void printTree(Tree *p, int level) { //printing func from Uni`s example
    if(p){    
        printTree(p->left, level + 1); 
        for (int i = 0; i<level; i++){   
            cout<<"   ";
        }
        cout<<p->data.number<<endl;
        printTree(p->right, level + 1);
        }
}

void print2DTree(Tree *root, int space) {  //I prefer this printing func
    if (root == NULL)  
        return;  
  
    space += COUNT;  
  
    print2DTree(root->right, space);  
  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->data.number<<"\n";  

    print2DTree(root->left, space);  
}