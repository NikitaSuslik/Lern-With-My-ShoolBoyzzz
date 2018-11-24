#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

enum mode_e {stack = 1, qeue = 2};//Перечеслением задаем режим работы(стек или очередь)

static int head = 0;        //Это наша голова в ней будет храниться позиция для записи следующего элемента
                            //       0  1  2  3  4   5  |head(в данном случае 6)
                            //      [6][2][5][7][12][3][]
const int sizeA = 128;      //Размер массива
int* myarray;               //Указатель на массив(сам массив будет создан позже)
static int mode;            //Переменная хранящая режим работы


int pop();                  //Возвращает число из массива
void push(int key);         //Добавляет число в массив
bool empty();               //Если массив пустой возвращает true
void savearray();           //Сохраняет массив в файл(filePath ниже)
void loadarray();           //Загружает массив из файла(filePath ниже)
static const char filePath[] = "/Users/nikita/Desktop/Univer/stack.txt";    //Если вы в винде, (а вы в винде, она же ахуенная!!!),
                                                                            //то после равно в кавычках напишите "любое_название_файла.bin"
                                                                            //например "I_love_Cpp.bin"

int main()
{
    for(int i = 0; i < sizeA; i++) myarray[i] = 0;      //Тупо зануление массива, вообще не обязательно, просто признак хорошего тона
                                                        //занулять все что можно
    cout << "*******************STACK/QEUE*******************\n";
    char command;                                       //Воодим переменую, которая будет хранить в себе команды введенные пользователями
    cout << "Вы хотите создать новый массив или загрузить имеющийся из файла?(n - Создать новый, l - Загрузить)"; //Думаю тут понятно
    cin >> command;
    bool chose = false;             //Небольшой костыльчик, который будет хранить в себе состояние определился ли пользователь с созданием
                                    //массива или загрузкой из файла
    while(!chose){                  //Проверка на сдеоан ли выбор
        switch (command) {          //Передаем нашу переменную с выбором
        case 'n':                   //Если введена "n"
            myarray  = new int [sizeA];     //Создание нового массива
            cout << "Выберите режим работы (stack - 1, qeue - 2): ";    //Тут понятно(надеюсь)
            while (mode != mode_e::qeue && mode != mode_e::stack){       //Пока пользователь не введет разрешенные цифры - выполнять цикл считывания
                cin >> mode;        //Считываем
                if (mode != mode_e::qeue && mode != mode_e::stack) cout << "Введите только те значения, которые даны!\n";
            }
            cout << "Выбран режим ";
            switch (mode) {
            case mode_e::stack:     //Если выбран режим стека
                cout << "стека\n";
                break;
            case mode_e::qeue:      //Если выбран режим очереди
                cout << "очереди\n";
                break;
            }
            chose = true;           //Режим выбран - значит вывалимся из цикла
            break;                  //Что бы не выполнился следующий кейс
        case 'l':                   //Если введена "l"
            myarray = new int [sizeA]; //Создаем массив
            loadarray();            //Грузим массив из файла
            chose = true;           //Режим выбран - значит вывалимся из цикла
            break;                  //Что бы не выполнился дефолт
        default:
            cout << "Введите допустимые значения!!!";
            break;
        }
    }

    cout << "Введите \"q\" - чтобы выйти,\n"                            //Менюшка :3
            "\"a\" - что бы добавить число в массив,\n"
            "\"g\" - что бы изъять число из массива,\n"
            "\"i\" - выполнить проверку на наличие элементов в массиве\n"
            "\"s\" - что бы сохранить массив\n";

    while (true){                       //Бесконечный цикл
        cin >> command;                 //Считываем команду из менюшки
        switch (command) {
        case 'q':                       //Выход
            exit(0);                    //Это выход из программы вообще как в конце main return 0;
                                        //Параметр exit(int exit_code)
                                        //Например exit(0) это как return 0; в конце main
                                        //или exit(1) как return 1; в конце main
            //break;                    //break; тут не обязателен т.к. после exit(0) все равно ничего больше не выполнится
        case 'a':                       //Добавление
            cout << "Введите число: ";
            int key;                    //Переменная для числа добавляемого в массива
            cin >> key;
            push(key);                  //Используем пуш для добавления
            break;                      //Что бы не перейти в следующий кейс
        case 'g':
            cout << "Изъятое число: " << pop() << "\n"; //Изымаем с помощью pop();
            break;  //Понятно
        case 'i':
            if(empty()) cout << "Массив пуст!"; //Используем функцию empty();
            else cout << "Массив не пуст!";
            break;
        case 's':
            savearray();                //Используем функцию сохранения
            break;
        default:
            cout << "Неизвестная команда, попробуйте еще раз!";
        }
    }
    return 0;           //Может выдавать варнинг, типо "Слышь, кодер от бога, ретурн никогда не выполниться, у тебя, по ходу,
                        //ошибка где то, ищи давай!" - ясен красен, у нас выше бесконечный цикл, да и выход из
                        //программы у нас есть 'q', так что шлем его нахер, но не забываем сказать спасибо
                        //ибо работу свою компилятор выполнил
}


bool empty(){//##############################################################################EMPTY
    return head == 0;       //head == 0; вернет булево значение, оно нам и надо, сразу его в ретурн функции
}


void push(int key){//##############################################################################PUSH
    if(head == sizeA) cout << "Массив переполнен";  //Если Голова находится на позиции равной размеру массива то выводим предупреждение
    else {
        myarray[head++] = key;  //Записываем  ячейку с индексом head и после выполнения записи увеличиваем head таким
                                //образом наше правило(выше) будет соблюдаться
    }
}


int pop(){//##############################################################################POP
    if(!empty()){               //Перед взятием элемента проверяем на пустоту массива
        switch (mode) {         //Свитч схож с теми, что были раньше
        case mode_e::stack:
            return myarray[--head]; //Сначала декрементируем Голову затем возвращаем значение в массиве по индексу головы FILO

        case mode_e::qeue:
            int tmp = myarray[0];   //Изымаем значение из нулевого элемента во временную переменную
                                    //т.к. следующий цикл затрет нулевой элемент, а он нам нужен
                                    //таким образом какой элемент первый зашел, первым он и уйдет FIFO
            for(int i = 1; i < head; i++) myarray[i-1] = myarray[i];    //Сдвигаем все элементы к началу массива
                                                                        //пробигаем до головы так как в голове - 1 последний элемент
            head--;                                                     //Декрементируем Голову
            return tmp;             //Возвращаем временную переменную
        }
    }
    else {                          //Если массив пуст
        cout << "Массив пуст!!!";
    }
    return 0;
}



void savearray(){//##############################################################################SAVEARRAY
    ofstream oFile;                                             //Создаем объект типа ofstream выходной поток в файл
    oFile.open(filePath, ios_base::trunc | ios_base::binary);   //Имя файла это filePath, флаги: trunc - очистка перед открытием
                                                                //binary - бинарный режим
    if(oFile.is_open()){                                        //Проверка на открыт ли файл
        oFile.write((const char*)&mode, sizeof (int));          //Пишем сначала режим работы с массивом(размером инт) это первый инт
        oFile.write((const char*) myarray, head * sizeof(int)); //Теперь пишем весь массив(с явным приведением типов указателей)
                                                                //размером до нашей головы умноженное на количество байт
                                                                //выделяемое под инт
    }
    else cout << "Ошибка открытия файла!(В сохранении)";
}

void loadarray(){//##############################################################################LOADARRAY
    ifstream iFile;                                 //Создаем объект типа ifstream входной поток из файла
    iFile.open(filePath, ios_base::binary);         //Открыаем с режимом binary
    head = 0;                                       //Обнуляем голову хотя не обязательно но как было сказано обнуляем все, что можно :3
    if(iFile.is_open()){                            //Проверка на открытый файл
        iFile.read((char*)&mode, sizeof(int));      //Читаем первый инт и пишем в режим
        while (!iFile.eof()){                       //Читаем пока не конец файла
            int key = 0;                            //Создаем временную переменную и обнуляем(сечешь зачем?))0)00)
            iFile.read((char*)&key, sizeof(int));   //Читаем в этот кей размером инт
            if(!iFile.eof()) push(key);             //И пишем в массив
        }
        switch (mode) {                             //Видим знакомый свитч
        case mode_e::stack:
            cout << "Открыт режим стека";
            break;
        case mode_e::qeue:
            cout << "Открыт режим очереди";
            break;
        }
    }
    else cout << "Ошибка открытия файла!(В загрузке)";
}
