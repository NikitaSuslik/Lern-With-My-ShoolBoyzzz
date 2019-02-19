#ifndef TREE_H
#define TREE_H

#include<iostream>
using namespace std;

struct node
{
    int key;
    node* left;
    node* right;
};

static node* root;

void push(int key);
void push(int key, node* parent);
void print(node* parent);
void print();
node* search(int key);
node* search(int key, node* );


#endif // TREE_H
