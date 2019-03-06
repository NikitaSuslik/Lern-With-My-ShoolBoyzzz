#ifndef TREE_H
#define TREE_H

#include<iostream>
class node{
public:
    node();
    int key;
    node* left;
    node* right;
    node* parent;
};
using namespace std;
class tree{
public:

    node* root;

    tree();
    tree(tree& t1);
    void push(int key);
    void push(int key, node* parent);
    void print(node* parent);
    void print();
    node* search(int key);
    node* search(int key, node* );
    void copy(node* second, node* first);
    bool remove(int key);
    void move(node* start);
};


#endif // TREE_H
