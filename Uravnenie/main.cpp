#include <iostream>
#include <fstream>
#include <clocale>

using namespace std;

float sum(const float* mas, const int mas_count);                           //расчет суммы элементов в массиве
float quart(const float);                                                   //расчет квадрата
float sum_ad(const float* masX, const float* masY, const int mas_count);    //расчет суммы произведений двух массивов
float sum_qrt(const float* mas, const int mas_count);                       //расчет суммы квадратов элементов
float find_a(const float* masX, const float* masY, const int mas_count);    //поиск а
float find_b(const float* masX, const float* masY, const int mas_count);    //поиск b

bool readData(string path, float*& X, float*& Y, int* mas_count);           //чтение данных из файла по пути path
                        //в параметрах передаются указатели в которые функция запишет указатели на массив Х, массив Y и число элементов
char* getPathToData(const char* argv_0);                                    //определение текущей директории и добавление "testData.test"



int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    int mas_count = 0;              //создание и инициализация переменных   )
    float* X = nullptr;             //                                      )
    float* Y = nullptr;             //                                      )
    string path;                    //                                      )
    char com = '\0';                //                                      )

    cout << "Выберите откуда загрузить тестовые данные: 0 - из директории с исполняемым файлом(testData.test), 1 - прописать путь вручную\n";
    while(com != '0' && com != '1'){        //цикл чтения потока ввода, пока пользователь не введет 0 или 1
        com = cin.get();                    //читаем один символ из потока
        cin.clear();                        //чстим поток
        if(com != '0' && com != '1'){       //если введено не 0 или 1 выводится предупреждение
            cout << "Выберите 0 или 1\n";
        }
    }
    switch (com) {
    case '0':                           //пользователь выбрал поиск файла в текущей директории
        path = getPathToData(argv[0]);  //argv[0] хранит в себе путь до исполнямого файла
        break;
    case '1':                           //пользователь решил ввести путь вручную
        cout << "Введите путь до файла с тестовыми данными: ";
        cin >> path;
        break;
    }
    if(!readData(path,X,Y,&mas_count)){ //попытка чтения из файла
        cout << "Ошибка при чтении";
        getchar();
        return 1;
    }

    cout << "a = " << find_a(X, Y, mas_count) << "\n";  //Вывод а
    cout << "b = " << find_b(X, Y, mas_count) << "\n";  //Вывод b
    getchar();
    return 0;
}


float sum(const float* mas, int mas_count){
    float res = 0;              //Временная переменная
    for(int i = mas_count-1; i >= 0; i--){
        res += mas[i];          //бегая по массиву суммируем все его элементы
    }
    return res;
}

float quart(const float a){
    return a * a;
}

float sum_ad(const float* masX, const float* masY, const int mas_count){
    float tmp_ad[mas_count];    //Временный массив с произведениями элементов
    for (int i = mas_count-1; i >= 0; i--) {
        tmp_ad[i] = masX[i] * masY[i];  //записываем во временный массив произведения элементов двух массивов
    }
    return sum(tmp_ad, mas_count);      //Возвращаем сумму всех элементов временного массива
}

float sum_qrt(const float* mas, const int mas_count){
    float res = 0;              //Временная переменная
    for(int i = mas_count-1; i >= 0; i--){
        res += quart(mas[i]);   //бегая по массиву находим квадраты его элементов и пишем их во временную переменную
    }
    return res;
}

float find_a(const float* masX, const float* masY, const int mas_count){
    //находим а по формуле:
    //    sum(x)*sum(y) - n*sum(x*y)
    //a = -------------------------
    //    qrt(sum(x)) - n*sum(qrt(x))
    return (sum(masX, mas_count)*sum(masY, mas_count) - mas_count * sum_ad(masX, masY, mas_count))/(quart(sum(masX, mas_count))-mas_count * sum_qrt(masX, mas_count));
}

float find_b(const float* masX, const float* masY, const int mas_count){
    //находим а по формуле:
    //    sum(x)*sum(x*y) - sum(qrt(x))*sum(y)
    //b = ----------------------------------
    //        qrt(sum(x)) - n*sum(qrt(x))
    return (sum(masX, mas_count)*sum_ad(masX, masY, mas_count) - sum_qrt(masX, mas_count)*sum(masY, mas_count))/(quart(sum(masX, mas_count))-mas_count * sum_qrt(masX, mas_count));
}


bool readData(string path, float*& X, float*& Y, int *mas_count){
    ifstream iFile;
    iFile.open(path, ios_base::in); //открываем файл на чтение
    if(!iFile.is_open())
        return false;
    iFile.read((char*)mas_count, sizeof (int));         //Читаем количество элементов
    X = new float[*mas_count];                          //выделяем память подд то количество, которое прочитали
    Y = new float[*mas_count];                          //выделяем память подд то количество, которое прочитали
    iFile.read((char*)X, sizeof(float)*(*mas_count));   //читаем сразу весь массив Х и У размером прочитанного количества  
    iFile.read((char*)Y, sizeof(float)*(*mas_count));
    iFile.close();                                      
    return true;
}

char* getPathToData(const char* argv_0){
    char* path = new char[255];
    strcpy(path, argv_0);
    int i = 0, last_s = 0;  
    while (path[i] != '\0') {       //с помощью этого цикла мы отрезаем от пути название самого исполняемого файла
        //например на входе в этот цикл в path будет "C:\\Users\nikita\Desktop\Uravnenie.exe"
        if(path[i] == '/' || path[i] == '\\')
            last_s = ++i;
        i++;
    }
        //на выходе из цикла в path будет "C:\\Users\nikita\Desktop\"
    strcpy(path + last_s, "testData.test");
        //тут в  path будет "C:\\Users\nikita\Desktop\testData.test"
    return path;
}
