#include <iostream>

using namespace std;

float sum(const float* mas, const int mas_count);
float quart(const float);
float sum_ad(const float* masX, const float* masY, const int mas_count);
float sum_qrt(const float* mas, const int mas_count);
float find_a(const float* masX, const float* masY, const int mas_count);
float find_b(const float* masX, const float* masY, const int mas_count);




int main()
{
    const int mas_count = 10;
    float X[mas_count] = {1.2, 4.2, 3.5, 2.6, 4.7, 3.1, 3.4, 1.2, 3.9, 3.7};
    float Y[mas_count] = {3, 12, 12, 8.9, 13, 11, 8.8, 5.2, 12.3, 10.5};

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
