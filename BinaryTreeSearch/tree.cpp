#include "tree.h"


void tree::push(int key, node *parent)
{
    if(key >= parent->key){
        if(parent->right){
            push(key, parent->right);
        }
        else{
            parent->right = new node();
            parent->right->parent = parent;
            parent->right->key = key;
        }
    }
    else{
        if(parent->left){
            push(key, parent->left);
        }
        else {
            parent->left = new node();
            parent->left->parent = parent;
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
        second->left->parent = second;
        copy(second->left, first->left);
    }
    if(first->right){
        second->right = new node();
        second->right->key = first->right->key;
        second->right->parent = second;
        copy(second->right, first->right);
    }
}

bool tree::remove(int key)
{
    node* findNode = search(key);
    node* parent = findNode->parent;
    if(!findNode) return false;
    if(!findNode->left && !findNode->right){
        if(findNode->key >= parent->key){
            parent->right = nullptr;
        }
        else{
            parent->left = nullptr;
        }
    }
    else if (findNode->right && !findNode->left) {
        node* tmp_Right = findNode->right;
        if(findNode->key >= parent->key){
            parent->right = tmp_Right;
        }
        else {
            parent->left = tmp_Right;
        }
    }
    else if (!findNode->right && findNode->left) {
        node* tmp_Left = findNode->left;
        if(findNode->key >= parent->key){
            parent->right = tmp_Left;
        }
        else {
            parent->left = tmp_Left;
        }
    }
    else{
        node* tmp;
        if(findNode->key >= parent->key){
            tmp = findNode->left->right;
            parent->right = findNode->left;
            findNode->left->right = findNode->right;
            if(tmp)
                move(tmp);
        }
        else {
            tmp = findNode->right->left;
            parent->left = findNode->right;
            findNode->right->left = findNode->left;
            if(tmp)
                move(tmp);
        }
    }
    delete findNode;
    return true;
}

void tree::move(node *start)
{
    if(start->left){
        move(start->left);
    }
    if(start->right){
        move(start->right);
    }
    push(start->key);
    delete start;
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
