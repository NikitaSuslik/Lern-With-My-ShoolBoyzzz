#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <istream>


#include "basestudent.h"

using namespace std;

struct StudentNode {
public:
    student* studentData = nullptr;
    StudentNode* nextStud = nullptr;
    StudentNode* prevStud = nullptr;
};

struct StudentList
{
public:
    //open

    //system
    StudentList() {}
    ~StudentList();
    bool empty();
    void addStudent();
    void deleteSudent();
    bool saveBase();
    void changeSort();
    bool loadBase();
    void printInfoStudent(bool fullInfo = false);
    void printInfoBase();
    StudentNode* findStudent(const char* lastname);
    //Interface
    void ShowMenu();
    void Initialize();


private:
    //Data
    StudentNode* point = nullptr;
    StudentNode* last = nullptr;
    StudentNode* first = nullptr;
    int size = 0;
    int iteration = 0;
    enum sorting {up, down};
    sorting sort = sorting::up;

    //Functions

    void addStudent(student*);

};

#endif // STUDENTLIST_H
