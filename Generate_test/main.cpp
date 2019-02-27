#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

float* genX(int count);
float* genY(const float a, const float b, int count);
void write_test(const float* X,const  float* Y,const  int count);

int main()
{

    return 0;
}


float* genX(int count){
    float* X = new float[count];
    for (int i = count-1;i >= 0;i--) {
        X[i] = 0.5 * (rand_r(time(NULL))%100);
        float delta;
        if(rand_r(time(NULL))%2 == 0)
            delta = 0.5 * (rand_r(time(NULL))%10);
        else
            delta = 0.5 * (rand_r(time(NULL))%10) * -1;
        X[i] -= delta;
    }
    return X;
}

float* genY(const float a, const float b, float* X, int count){
    float* Y = new float[count];
    for (int i = count-1;i >= 0;i--) {
        Y[i] = a*X[i] - b;
        float delta;
        if(rand_r(time(NULL))%2 == 0)
            delta = 0.5 * (rand_r(time(NULL))%10);
        else
            delta = 0.5 * (rand_r(time(NULL))%10) * -1;
        Y[i] -= delta;
    }
}

void write_test(const char* path, const float* X,const  float* Y,const  int count){
    ofstream oFile();

}
