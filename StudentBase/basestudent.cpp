#include "basestudent.h"




student::student(int id, const char *name, const char *secondname, const char *lastname, const char *birthday, const char *groupe)
{
    this->id = id;
    strcpy(this->name, name);
    strcpy(this->secondname, secondname);
    strcpy(this->lastname, lastname);
    strcpy(this->birthday, birthday);
    strcpy(this->groupe, groupe);
}

int student::getID(){
    return id;
}

char* student::getName(){
    return name;
}

char* student::getLastName(){
    return lastname;
}

char* student::getSecondName(){
    return secondname;
}

char* student::getGroupe(){
    return groupe;
}

char* student::getBirthDay(){
    return birthday;
}
