#include <iostream>
#include <time.h>
#include <fstream>
#include <random>
#include <clocale>
using namespace std;

float* genX(int count);
float* genY(const float a, const float b, float* X, int count);
bool write_test(const char* path, const float* X,const  float* Y,const  int count);
char *getStartPath(char* argv_0);

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    setlocale(LC_ALL, "rus");
    char* path = nullptr;
    float a = 0, b = 0;
    int cnt = 0;
    char com = '\0';
    cout << "Выберите куда сохранить тестовые данные: 0 - в директорию с исполняемым файлом, 1 - прописать путь вручную\n";
    while(com != '0' && com != '1'){
        com = cin.get();
        cin.clear();
        if(com != '0' && com != '1'){
            cout << "Выберите 0 или 1\n";
        }
    }
    switch (com) {
    case '0':
        path = getStartPath(argv[0]);
        break;
    case '1':
        cout << "Введите путь куда сохранить тестовые данные: ";
        cin >> path;
        break;
    }
    cout << "\nВведите a: ";
    cin >> a;
    cout << "\nВведите b: ";
    cin >> b;
    cout << "\nВведите число точек: ";
    cin >> cnt;

    float* X = genX(cnt);
    float* Y = genY(a,b, X, cnt);

    cout << "X = {";

    for (int i = cnt; i >= 0;i--) {
        if(i == 0)
            cout << X[i] << "}\n";
        else
            cout << X[i] <<",\t";
    }
    cout << "Y = {";

    for (int i = cnt; i >= 0;i--) {
        if(i == 0)
            cout << Y[i] << "}\n";
        else
            cout << Y[i] <<",\t";
    }

    if(write_test(path, X, Y, cnt)){
        cout << "\nГенерация прошла успешно\n";
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
    strcat(tmpPath, "testData.test");
    oFile.open(tmpPath, ios_base::trunc | ios_base::out);
    if(!oFile.is_open()){
        return false;
    }
    oFile.write((const char*)&count, sizeof (int));
    oFile.write((const char*)X, sizeof (float)*count);
    oFile.write((const char*)Y, sizeof (float)*count);
    oFile.close();
    return true;
}

char* getStartPath(char* argv_0){
    char* path = strcpy(nullptr, argv_0);
    int i = 0, last_s = 0;
    while (path[i] != '\0') {
        if(path[i] == '/');
            last_s = i;
        i++;
    }
    path.erase(last_s);
    return path;
}
