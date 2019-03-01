#include <iostream>
#include <time.h>
#include <fstream>
#include <random>
#include <clocale>
#include <stdio.h>
using namespace std;

float* genX(int count);                                                             //генератор Х
float* genY(const float a, const float b, float* X, int count);                     //генератор У
bool write_test(const char* path, const float* X,const  float* Y,const  int count); //запись тестовых данных в файл в машинном понимании
bool write_test_txt(const char* path, const float* X, const  float* Y, const  int count, const float a, const float b); //запись тестовых данных в файл в человеческом понимании
char *getStartPath(char* argv_0);   //получение пути до директории с исполняемым файлом

int main(int argc, char *argv[])
{
    srand(time(nullptr));               //настройка рандомных чисел
    setlocale(LC_ALL, "rus");

    char* path = nullptr;       //Создание и инициализация переменных   )
    float a = 0, b = 0;         //                                      )
    int cnt = 0;                //                                      )
    char com = '\0';            //                                      )
    cout << "Выберите куда сохранить тестовые данные: 0 - в директорию с исполняемым файлом, 1 - прописать путь вручную\n";
    while(com != '0' && com != '1'){        //цикл чтения потока ввода, пока пользователь не введет 0 или 1
        com = cin.get();                    //читаем один символ из потока
        cin.clear();                        //чстим поток
        if(com != '0' && com != '1'){       //если введено не 0 или 1 выводится предупреждение
            cout << "Выберите 0 или 1\n";
        }
    }
    switch (com) {
    case '0':                               //пользователь выбрал расположение файла в директории с исполняемым файлом
        path = getStartPath(argv[0]);
        break;
    case '1':                               //пользователь выбрал ручной ввод
        cout << "Введите путь куда сохранить тестовые данные: ";
        cin >> path;
        break;
    }
    cout << "\nВведите a: ";
    cin >> a;                               //введение коэффициента а
    cout << "\nВведите b: ";
    cin >> b;                               //введение коэффициента b
    cout << "\nВведите число точек: ";
    cin >> cnt;                             //введение количества элементов

    float* X = genX(cnt);                   //генерируем Х
    float* Y = genY(a,b, X, cnt);           //генерируем У

    if(write_test(path, X, Y, cnt)){
        cout << "\nГенерация прошла успешно\n";
    }
    else
        cout << "\nОшибка при записи тестовых данных\n";

    if(write_test_txt(path, X, Y, cnt, a, b)){
        cout << "\nЧто бы ознакомится с результатами генерации пройдите по пути: \"" << path << "testData.txt";
    }
    else
        cout << "\nОшибка при записи тестовых данных\n";


    return 0;
}


float* genX(int count){
    float* X = new float[count];
    for (int i = count-1;i >= 0;i--) {
        X[i] = 0.3 * (rand()%100);
        float delta;
        if(rand()%2 == 0)
            delta = 0.3 * (rand()%10);
        else
            delta = 0.3 * (rand()%10) * -1;
        X[i] += delta;
    }
    return X;
}

float* genY(const float a, const float b, float* X, int count){
    float* Y = new float[count];
    for (int i = count-1;i >= 0;i--) {
        Y[i] = a*X[i] + b;
    }
    return Y;
}

bool write_test(const char *path, const float* X, const  float* Y, const  int count){
    ofstream oFile;
    char tmpPath[255];
    strcpy(tmpPath, path);
    oFile.open(strcat(tmpPath, "testData.test"), ios_base::trunc | ios_base::out | ios_base::binary);
    if(!oFile.is_open()){
        return false;
    }
    oFile.write((const char*)&count, sizeof (int));
    oFile.write((const char*)X, sizeof (float)*count);
    oFile.write((const char*)Y, sizeof (float)*count);
    oFile.close();
    return true;
}

bool write_test_txt(const char* path, const float* X,const  float* Y,const  int count,const float a,const float b){
    ofstream oFile;
    char tmpPath[255];
    strcpy(tmpPath, path);
    oFile.open(strcat(tmpPath, "testData.txt"),ios_base::out | ios_base::trunc);
    if(!oFile.is_open())
        return false;
    oFile << "Число элементов: " << count << "\n" ;
    oFile << "X = {";
    for (int i = 0; i < count;i++) {
        if(i == 0)
            oFile << X[i] << "}\n";
        else
            oFile << X[i] <<",\t";
    }
    oFile << "Y = {";

    for (int i = 0; i < count;i++) {
        if(i == 0)
            oFile << Y[i] << "}\n";
        else
            oFile << Y[i] <<",\t";
    }
    oFile << "\na = " << a << "\nb = " << b;
}

char* getStartPath(char* argv_0){
    char* path = new char[255];
    strcpy(path, argv_0);
    int i = 0, last_s = 0;
    while (path[i] != '\0') {
        if(path[i] == '/' || path[i] == '\\')
            last_s = ++i;
        i++;
    }
    path[last_s] = '\0';
    return path;
}
