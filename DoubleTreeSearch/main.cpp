#include <iostream>
#include "tree.h"

using namespace std;



int main()
{

    push(10);
    push(5);
    push(15);
    push(3);
    push(2);
    push(17);
    push(13);
    print();
    node* find = search(15);
    if(!find){
        cout << "\nКлюча не существует\n";
    }
    else {
        cout << "\nНайденный ключ " << find->key << "\n";
    }

    return 0;
}
