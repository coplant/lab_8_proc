#ifndef CONTAINER_H
#define CONTAINER_H

#include <fstream>
#include <iostream>

using namespace std;

//Иднетификатор машины
enum Key {
    TRUCK, //Грузовик
    BUS, //Автобус
    PASSENGER_CAR //Легковой автомобиль
};

//Структура "машина"
struct Car {
    Key K; //Идентификатор машины
};

//Функция ввода машины
Car* In_Car(ifstream& ifst);

//Функция вывода машины
void Out_Car(Car* C, ofstream& ofst);

//Функция подсчет отношения груза к мощности
double Load_to_capacity_ratio(Car* C);

//Структура "грузовик"
struct Truck {
    Key K; //Идентификатор машины
    int Motor_power; //Мощность двигателя (из-за обобщения по ключу, 
                     //приходится хранить общий параметр в структуре каждой машины)
    int Load_cap; //Грузоподъемность
    double Fuel; //Расход топлива
};

//Функция ввода грузовика
Truck* In_Truck(ifstream& ifst);

//Функция вывода грузовика
void Out_Truck(Truck* T, ofstream& ofst);

//Функция подсчета отношения груза к мощности грузовика
double Load_to_capacity_ratio_Truck(Truck* T);

//Структура "автобус"
struct Bus {
    Key K; //Идентификатор машины
    int Motor_power; //Мощность двигателя (из-за обобщения по ключу, 
                     //приходится хранить общий параметр в структуре каждой машины)
    short int Passenger_cap; //Пассажировместимость
    double Fuel; //Расход топлива
};

//Функция ввода автобуса
Bus* In_Bus(ifstream& ifst);

//Функция вывода автобуса
void Out_Bus(Bus* B, ofstream& ofst);

//Функция подсчета отношения груза к мощности автобуса
double Load_to_capacity_ratio_Bus(Bus* B);

//Структура "легковой автомобиль"
struct Passenger_car {
    Key K; //Идентификатор машины
    int Motor_power; //Мощность двигателя (из-за обобщения по ключу, 
                     //приходится хранить общий параметр в структуре каждой машины)
    short int Max_speed; //Максимальная скорость
    double Fuel; //Расход топлива
};

//Функция ввода легкового автомобиля
Passenger_car* In_Passenger_car(ifstream& ifst);

//Функция вывода легкового автомобиля
void Out_Passenger_car(Passenger_car* P_c, ofstream& ofst);

//Функция подсчета отношения груза к мощности легкового автомобиля
double Load_to_capacity_ratio_Passenger_car(Passenger_car* P_c);

//Контейнер
struct Container {
    int Len; //Длина контейнера
    Car* Cont; //Указатель на машину
    Container* Prev; //Указатель на предыдущий элемент контейнера
    Container* Next; //Указатель на следующий элемент контейнера
};

//Функция инициализации контейнера
void Init_Container(Container* Head, Container* Tail);

//Функция ввода элементов в контейнер
void In_Container(Container* Head, Container* Tail, ifstream& ifst);

//Функция вывод контейнера
void Out_Container(Container* Head, ofstream& ofst);

//Функция очистки контейнера
void Clear_Container(Container* Head, Container* Tail);

//Функция сравнения элементов контейнера
bool Compare(Container* First, Container* Second);

//Функция сортировки
void Sort(Container* Head);

//Функция вывода только грузовиков
void Out_Only_Truck(Container* Head, ofstream& ofst);

#endif //CONTAINER_H