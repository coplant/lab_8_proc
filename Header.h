#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//Класс "машина"
class Car {
    int Motor_power; //Мощность мотора
    double Fuel; //Расход топлива
public:
    void Set_Motor_power(int _Motor_power);
    int Get_Motor_power();

    void Set_Fuel(double _Fuel);
    double Get_Fuel();

    static Car* In_Car(ifstream& ifst); //Функция ввода информации о машине
    virtual void In_Data(ifstream& ifst) = 0; //Чисто вирутальная функция ввода информации
                                              //о машине, она будет определена для
                                              //каждого класса машин
    virtual void Out_Data(int Motor_power, double Fuel, ofstream& ofst) = 0; //Чисто вирутальная функция вывода информации
                                              //о машине, она будет определена для
                                              //каждого класса машин
    virtual double Load_to_capacity_ratio(int Motor_power) = 0; //Функция подсчета отношения груза к мощности
    bool Compare(Car* Other); //Функция сравнения отношений груза к мощности
    virtual void Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst); //Функция вывода только грузовиков
protected:
    Car() {};
};

//Класс "грузовик"
class Truck : public Car {
    int Load_cap; //Грузоподъемность
public:
    void Set_Load_cap(int _Load_cap);
    int Get_Load_cap();

    void In_Data(ifstream& ifst); //Функция ввода информации о грузовик
    void Out_Data(int Motor_power, double Fuel, ofstream& ofst); //Функция вывода информации о грузовике
    double Load_to_capacity_ratio(int Motor_power); //Функция подсчета отношения груза к мощности
    void Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst); //Функция вывода только грузовиков
    Truck() {};
};

//Класс "автобус"
class Bus : public Car {
    short int Passenger_cap; //Пассажировместимость
public:
    void Set_Passenger_cap(short int _Passenger_cap);
    short int Get_Passenger_cap();

    void In_Data(ifstream& ifst); //Функция ввода информации об автобусе
    void Out_Data(int Motor_power, double Fuel, ofstream& ofst); //Функция вывода информации об автобусе
    double Load_to_capacity_ratio(int Motor_power); //Функция подсчета отношения груза к мощности
    Bus() {};
};

//Класс "легковой автомобиль"
class Passenger_car : public Car {
    short int Max_speed; //Максимальная скорость
public:
    void Set_Max_speed(short int _Max_speed);
    short int Get_Max_speed();

    void In_Data(ifstream& ifst); //Функция ввода информации о легковом автомобиле
    void Out_Data(int Motor_power, double Fuel, ofstream& ofst); //Функция вывода информации о легковом автомобиле
    double Load_to_capacity_ratio(int Motor_power); //Функция подсчета отношения груза к мощности
    Passenger_car() {};
};

//Узел контейнера
struct Node {
    Node* Next, * Prev; //Указатель на следующий и предыдущий элементы контейнера
    Car* Cont; //Указатель на машину
};

//Контейнер
class Container {
    Node* Head, *Tail; //Указатели на "голову" и "хвост" контейнера
    int Len; //Размерность контейнера
public:
    void Set_Head(Node* _Head);
    Node* Get_Head();

    void Set_Tail(Node* _Tail);
    Node* Get_Tail();

    void Set_Len(int _Len);
    int Get_Len();

    void In(ifstream& ifst); //Функция ввода элемента в контейнер
    void Out(ofstream& ofst); //Функция вывода элемента из контейнера
    void Clear(); //Функция очищения контейнера
    void Sort(); //Функция сортировки контейнера
    void Out_Only_Truck(ofstream& ofst); //Функция вывода только грузовиков
    Container(); //Конструктор
    ~Container() { Clear(); } //Деструктор
};

#endif //HEADER_H