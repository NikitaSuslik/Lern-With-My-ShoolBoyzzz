#include <iostream>
#include "tree.h"

using namespace std;



int main()
{
    tree myTree;
    myTree.push(10);
    myTree.push(5);
    myTree.push(15);
    myTree.push(3);
    myTree.push(2);
    myTree.push(17);
    myTree.push(13);
    cout << "\nFirst tree\n";
    myTree.print();
    tree secondtree = myTree;
    cout << "\nSecond tree\n";
    secondtree.print();
    node* find = myTree.search(15);
    if(!find){
        cout << "\nКлюча не существует\n";
    }
    else {
        cout << "\nНайденный ключ " << find->key << "\n";
    }

    return 0;
}
