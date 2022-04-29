#include <iostream>

#include "Header.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << endl;
        exit(1);
    }

    ifstream ifst(argv[1]);

    ofstream ofst(argv[2]);

    cout << "Start" << endl;

    Container* Head = new Container(); //Создаем "голову" контейнера
    Container* Tail = new Container(); //Создаем "хвост" контейнера

    Init_Container(Head, Tail); //Инициализируем контейнер

    In_Container(Head, Tail, ifst); //Записываем элементы в контейнер

    ofst << "Filled and sorted container. " << endl;

    Sort(Head); //Сортировка контейнера

    Out_Container(Head, ofst); //Вывод контейнера

    Out_Only_Truck(Head, ofst); //Вывод только грузовиков

    Clear_Container(Head, Tail); //Очистка контейнера

    ofst << "Empty container. " << endl;

    Out_Container(Head, ofst); //Вывод контейнера

    cout << "Stop" << endl;
    system("pause");
    return 0;
}
