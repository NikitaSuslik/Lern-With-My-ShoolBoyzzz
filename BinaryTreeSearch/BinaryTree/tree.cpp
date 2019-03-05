#include "tree.h"


void tree::push(int key, node *parent)
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

void tree::push(int key)
{
    if(root){
        push(key, root);
    }
    else {
        root = new node();
        root->key = key;
    }
}

void tree::print(node *parent)
{
    if(parent->left)
        print(parent->left);

    cout << "{ " << parent->key << " }";

    if(parent->right)
        print(parent->right);

}

void tree::print()
{
    print(root);
}

node* tree::search(int key)
{
    if(root){
        return search(key, root);
    }
    else{
        cout << "\nДерева не существует";
        return nullptr;
    }
}

node* tree::search(int key, node* parent){
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

void tree::copy(node *second, node *first)
{
    if(first->left){
        second->left = new node();
        second->left->key = first->left->key;
        copy(second->left, first->left);
    }
    if(first->right){
        second->right = new node();
        second->right->key = first->right->key;
        copy(second->right, first->right);
    }
}

tree::tree(){
    root = nullptr;
}

tree::tree(tree &t1)
{
    if(t1.root){
        this->root = new node();
        this->root->key = t1.root->key;
        copy(this->root, t1.root);
    }

}

node::node(){
    left = nullptr;
    right = nullptr;
    key = 0;
}
