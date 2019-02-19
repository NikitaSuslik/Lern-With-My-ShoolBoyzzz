#include "tree.h"


void push(int key, node *parent)
{
    if(key >= parent->key){
        if(parent->right){
            push(key, parent->right);
        }
        else{
            parent->right = new node();
            parent->right->key = key;
        }
    }
    else{
        if(parent->left){
            push(key, parent->left);
        }
        else {
            parent->left = new node();
            parent->left->key = key;
        }
    }
}

void push(int key)
{
    if(root){
        push(key, root);
    }
    else {
        root = new node();
        root->key = key;
    }
}

void print(node *parent)
{
    if(parent->left)
        print(parent->left);

    cout << "{ " << parent->key << " }";

    if(parent->right)
        print(parent->right);

}

void print()
{
    print(root);
}

node *search(int key)
{
    if(root){
        return search(key, root);
    }
    else{
        cout << "\nДерева не существует";
        return nullptr;
    }
}

node* search(int key, node* parent){
    if(key > parent->key){
        if(parent->right){
            return search(key, parent->right);
        }
        else{
            return nullptr;
        }
    }
    else if(key == parent->key){
        return parent;
    }
    else{
        if(parent->left){
            return search(key, parent->left);
        }
        else{
            return nullptr;
        }
    }
}
