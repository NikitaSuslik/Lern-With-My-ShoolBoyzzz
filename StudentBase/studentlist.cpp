#include "studentlist.h"


bool StudentList::empty()
{
    return first == nullptr;
}

void StudentList::addStudent()
{
    cout << "Print info about student:\nName ";
    char name[sizeArray];
    cin >> name;
    cout << "\nLastname: ";
    char lastname[sizeArray];
    cin >> lastname;
    cout << "\nSecondname: ";
    char secondname[sizeArray];
    cin >> secondname;
    cout << "\nGroupe: ";
    char groupe[sizeArray];
    cin >> groupe;
    cout << "\nBirthday(format dd.mm.yyyy): ";
    char birthday[sizeArray];
    cin >> birthday;
    iteration++;
    size++;
    StudentNode* n = new StudentNode;
    n->studentData = new student(iteration, (const char*) name, (const char*)secondname, (const char*)lastname, (const char*)birthday, (const char*) groupe);
    if(empty()) {
        first = last = n;
    }
    else {
        StudentNode* FindStud = findStudent(lastname);
        if (FindStud == nullptr) {
            first->prevStud = n;
            n->nextStud = first;
            first = n;
        }
        else if(strcmp(lastname, FindStud->studentData->getLastName()) >= 0){
            last->nextStud = n;
            n->prevStud = last;
            last = n;
        }
        else {
            n->prevStud = FindStud->prevStud;
            n->nextStud = FindStud;
            FindStud->prevStud = n;
            n->prevStud->nextStud = n;
        }
    }
}

void StudentList::deleteSudent()
{
    if(point == last) {
        last = point->prevStud;
        last->nextStud = nullptr;
        delete point;
    }
    else if(point == first){
        first = point->nextStud;
        first->prevStud = nullptr;
        delete point;
    }
    else if(first == last){
        delete point;
        first = last = nullptr;
    }
    else {
        StudentNode* tmpNext = point->nextStud;
        StudentNode* tmpPrev = point->prevStud;
        delete point;
        point = nullptr;
        tmpNext->prevStud = tmpPrev;
        tmpPrev->nextStud = tmpNext;
    }
    size--;
}

void StudentList::addStudent(student* stud)
{
    StudentNode* n = new StudentNode;
    n->studentData = stud;
    char* lastname = stud->getLastName();
    if(empty()) {
        first = last = n;
    }
    else {
        StudentNode* FindStud = findStudent(lastname);
        if (FindStud == nullptr) {
            first->prevStud = n;
            n->nextStud = first;
            first = n;
        }
        else if(strcmp(lastname, FindStud->studentData->getLastName()) >= 0){
            last->nextStud = n;
            n->prevStud = last;
            last = n;
        }
        else {
            n->prevStud = FindStud->prevStud;
            n->nextStud = FindStud;
            FindStud->prevStud = n;
            n->prevStud->nextStud = n;
        }
    }
}



bool StudentList::saveBase()
{
    ofstream oFile;
    oFile.open("/Users/nikita/Desktop/Data.my", ios_base::trunc | ios_base::binary);
    if(oFile.is_open()){
        oFile.write((const char*)&iteration,sizeof (int));
        point = first;
        while(point != nullptr){
            oFile.write((const char*)point->studentData, sizeof (student));
            point = point->nextStud;
        }
        oFile.close();
        return true;
    }
    else {
        return false;
    }

}

void StudentList::changeSort()
{
    switch (sort) {
    case sorting::up:
        sort = sorting::down;
        break;
    case sorting::down:
        sort = sorting::up;
        break;
    }
}

bool StudentList::loadBase()
{
    ifstream iFile;
    iFile.open("/Users/nikita/Desktop/Data.my", ios_base::binary);
    if(iFile.is_open()){
        iFile.read((char*)&iteration,sizeof (int));
        while(!iFile.eof()){

            int id = 0;
            char name[sizeArray] = {0};
            char lastname[sizeArray] = {0};
            char secondname[sizeArray] = {0};
            char groupe[sizeArray] = {0};
            char birthday[11] = {0};

            iFile.read((char*)&id, sizeof(int));
            iFile.read(name, sizeof(char)*sizeArray);
            iFile.read(lastname, sizeof(char)*sizeArray);
            iFile.read(secondname, sizeof(char)*sizeArray);
            iFile.read(groupe, sizeof(char)*sizeArray);
            iFile.read(birthday, sizeof(char)*12);
            if(!iFile.eof()){
                student* tmpStudent = new student(id, name, secondname, lastname, birthday, groupe);
                addStudent(tmpStudent);
            }
        }
        iFile.close();
        return true;
    }
    else return false;
}

void StudentList::printInfoStudent(bool fullInfo)
{
    if(fullInfo){
        cout << "Student: " << point->studentData->getLastName() << " "
             << point->studentData->getName() << " "
             << point->studentData->getSecondName() << "\n"
             <<"ID " << point->studentData->getID() << "\n"
             "Birtday " << point->studentData->getBirthDay() <<"\n"
             "Groupe " << point->studentData->getBirthDay() << "\n";
    }
    else {
        cout << point->studentData->getLastName() << " " << point->studentData->getName() <<"\n";
    }
}

void StudentList::printInfoBase()
{
    int iter = 1;
    char ans;
    while(1){
        cout << "Would you like see full info?(\"y\" - yes, \"n\" - no)\n";
        cin >> ans;
        cin.ignore(100,'\n');
        if(ans == 'y' || ans == 'n'){
            break;
        }
    }
    switch (sort) {
    case StudentList::sorting::up:
        point = first;
        while (point != nullptr){
            cout << "\n\n" << iter << " ################################# " << iter << "\n";
            if(ans == 'y')
                printInfoStudent(true);
            else
                printInfoStudent();
            point = point->nextStud;
            iter++;
        }
        break;
    case StudentList::sorting::down:
        point = last;
        while (point != nullptr){
            cout << "\n" << iter << " ################################# " << iter << "\n";
            if(ans == 'y')
                printInfoStudent(true);
            else
                printInfoStudent();
            point = point->prevStud;
            iter++;
        }
        break;
    }
}

StudentNode* StudentList::findStudent(const char *lastname)
{
    if(empty()) return  nullptr;
    else{
        point = first;
        char* tmpLastName = point->studentData->getLastName();
        if(strcmp(lastname, tmpLastName) < 0) return nullptr;
        while(strcmp(lastname, tmpLastName) > 0){
            if(point == last) return last;
            point = point->nextStud;
            tmpLastName = point->studentData->getLastName();
        }
        return point;
    }
}

void StudentList::ShowMenu()
{
    cout << "Please print:\n"
            "\"a\" - for adding student\n"
            "\"p\" - for printing base\n"
            "\"f\" - for find student\n"
            "\"e\" - check is empty\n"
            "\"c\" - for change sorting\n"
            "\"s\" - for save base\n"
            "\"l\" - for load base\n";
}

void StudentList::Initialize()
{
    char command = 'h';
    while (true){
        ShowMenu();
        cin >> command;
        cin.ignore(100,'\n');
        switch (command) {
        case 'a':
            addStudent();
            cout << "Student is create!\n";
            cin.get();
            break;
        case 'p':
            if(empty()){
                cout << "Base is empty!";
                cin.get();
                break;
            }
            printInfoBase();
            cout << "\nPress any key for quit\n";
            cin.get();
            break;
        case 'f':
            if(empty()){
                cout << "Base is empty!";
                cin.get();
                break;
            }
            char tmpLastName[sizeArray];
            cout << "Input Lastname for searching: ";
            cin >> tmpLastName;
            cin.ignore(100,'\n');
            cout << '\n';
            findStudent(tmpLastName);
            if(point != nullptr)
                if(strcmp(tmpLastName, point->studentData->getLastName()) != 0){
                    cout << "Student not found!\nPress any key for continue.\n";
                    cin.get();
                    break;
                }
            while (command != 'q') {
                cout << "Find student:\n";
                printInfoStudent();
                cout << "What is next?\n"
                        "\"d\" - delete\n"
                        "\"p\" - print full info\n"
                        "\"q\" - qiut\n";
                cin.get(command);
                cin.ignore(100,'\n');
                switch (command) {
                case 'd':
                    deleteSudent();
                    cout << "Student deleted\n";
                    command ='q';
                    break;
                case 'p':
                    printInfoStudent(true);
                    cout << "Press any key for continue.\n";
                    cin.get();
                    break;
                case 'q':
                    break;
                default:
                    cout << "Unknow command.\nTry again.\nPress any key for continue.\n";
                    cin.get();
                    system("clear");
                    break;
                }
            }
            break;
        case 'q':
            return;
        case 'c':
            changeSort();
            switch (sort) {
            case StudentList::sorting::up:
                cout << "Sort up\n";
                break;
            case StudentList::sorting::down:
                cout << "Sort down\n";
                cout << "Press any key for continue.\n";
                cin.get();
                break;
            }
            break;
        case 'e':
            if(empty()) cout << "Empty!\n";
            else cout << "Not empty!\n";
            cout << "Press any key for continue.\n";
            cin.get();
            break;
        case 's':
            if(saveBase()){
                cout << "Base is saved!\nPress any key for continue.\n";
                cin.get();
            }
            else {
                cout << "Error save!\nPress any key for continue.\n";
                cin.get();
            }
            break;
        case 'l':
            if(loadBase()){
                cout << "Base is loaded!\nPress any key for continue.\n";
                cin.get();
            }
            else {
                cout << "Error load!\nPress any key for continue.\n";
                cin.get();
            }
            break;
        default:
            cout << "Unkown commmand" << command << ".\nTry again.\nPress any key for continue.\n";
            cin.get();
            break;
        }
        system("clear");
    }
}




