#include <iostream>
#include <fstream>
#include <clocale>

using namespace std;

float sum(const float* mas, const int mas_count);
float quart(const float);
float sum_ad(const float* masX, const float* masY, const int mas_count);
float sum_qrt(const float* mas, const int mas_count);
float find_a(const float* masX, const float* masY, const int mas_count);
float find_b(const float* masX, const float* masY, const int mas_count);


bool readData(string path, float*& X, float*& Y, int* mas_count);



int main()
{
    setlocale(LC_ALL, "rus");
    int mas_count = 0;
    float* X = nullptr;
    float* Y = nullptr;
    string path;


    cout << "Введите путь до файла с тестовыми данными: ";
    cin >> path;
    if(!readData(path,X,Y,&mas_count)){
        cout << "Ошибка при чтении";
        getchar();
        return 1;
    }

    cout << "X = {";

    for (int i = mas_count; i >= 0;i--) {
        if(i == 0)
            cout << X[i] << "}\n";
        else
            cout << X[i] <<",\t";
    }
    cout << "Y = {";

    for (int i = mas_count; i >= 0;i--) {
        if(i == 0)
            cout << Y[i] << "}\n";
        else
            cout << Y[i] <<",\t";
    }

    cout << "a = " << find_a(X, Y, mas_count) << "\n";
    cout << "b = " << find_b(X, Y, mas_count) << "\n";

    return 0;
}


float sum(const float* mas, int mas_count){
    float res = 0;
    for(int i = mas_count-1; i >= 0; i--){
        res += mas[i];
    }
    return res;
}

float quart(const float a){
    return a * a;
}

float sum_ad(const float* masX, const float* masY, const int mas_count){
    float res = 0;
    float tmp_ad[mas_count];
    for (int i = mas_count-1; i >= 0; i--) {
        tmp_ad[i] = masX[i] * masY[i];
    }
    res = sum(tmp_ad, mas_count);
    return res;
}

float sum_qrt(const float* mas, const int mas_count){
    float res = 0;
    for(int i = mas_count-1; i >= 0; i--){
        res += quart(mas[i]);
    }
    return res;
}

float find_a(const float* masX, const float* masY, const int mas_count){
    return (sum(masX, mas_count)*sum(masY, mas_count) - mas_count * sum_ad(masX, masY, mas_count))/(quart(sum(masX, mas_count))-mas_count * sum_qrt(masX, mas_count));
}

float find_b(const float* masX, const float* masY, const int mas_count){
    return (sum(masX, mas_count)*sum_ad(masX, masY, mas_count) - sum_qrt(masX, mas_count)*sum(masY, mas_count))/(quart(sum(masX, mas_count))-mas_count * sum_qrt(masX, mas_count));
}

bool getCountMas(string path, int* mas_count){
    ifstream iFile;
    iFile.open(path, ios_base::in);
    if(!iFile.is_open())
        return false;
    iFile.read((char*)mas_count,sizeof (int));
    iFile.close();
    return true;
}

bool readData(string path, float*& X, float*& Y, int *mas_count){
    ifstream iFile;
    iFile.open(path, ios_base::in);
    if(!iFile.is_open())
        return false;
    iFile.read((char*)mas_count, sizeof (int));
    X = new float[*mas_count];
    Y = new float[*mas_count];
    iFile.read((char*)X, sizeof(float)*(*mas_count));
    iFile.read((char*)Y, sizeof(float)*(*mas_count));
    iFile.close();
    return true;
}
