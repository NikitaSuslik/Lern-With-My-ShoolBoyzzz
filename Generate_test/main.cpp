#include <iostream>
#include <time.h>
#include <fstream>
#include <random>

using namespace std;

float* genX(int count);
float* genY(const float a, const float b, float* X, int count);
bool write_test(const string path, const float* X,const  float* Y,const  int count);

int main()
{
    string path;
    float a = 0, b = 0;
    int cnt = 0;
    cout << "Write path to save test data: ";
    cin >> path;
    cout << "\nWrite a: ";
    cin >> a;
    cout << "\nWrite b: ";
    cin >> b;
    cout << "\nWrite max count points: ";
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
        cout << "\nGenerate is done\n";
    }
    else
        cout << "\nSome error...\n";


    return 0;
}


float* genX(int count){
    float* X = new float[count];
    for (int i = count-1;i >= 0;i--) {
        X[i] = 0.3 * (rand()%10);
        float delta;
        if(rand()%2 == 0)
            delta = 0.3 * (rand()%10);
        else
            delta = 0.3 * (rand()%1) * -1;
        X[i] += delta;
    }
    return X;
}

float* genY(const float a, const float b, float* X, int count){
    float* Y = new float[count];
    for (int i = count-1;i >= 0;i--) {
        Y[i] = a*X[i] - b;
        /*
        float delta;
        if(rand()%2 == 0)
            delta = 0.3 * (rand()%10);
        else
            delta = 0.3 * (rand()%1) * -1;
        Y[i] -= delta;
        */
    }
    return Y;
}

bool write_test(const string path, const float* X, const  float* Y, const  int count){
    ofstream oFile;

    oFile.open(path + "/testData.txt", ios_base::trunc | ios_base::out);
    if(!oFile.is_open()){
        return false;
    }
    oFile.write((const char*)&count, sizeof (int));
    for (int i = count-1; i >= 0;i--) {
        oFile.write((const char*)&X[i], sizeof (float));
    }
    for (int i = count-1; i >= 0;i--) {
        oFile.write((const char*)&Y[i], sizeof (float));
    }
    oFile.close();
    return true;
}
