#ifndef CONTAINER_H
#define CONTAINER_H

#include <fstream>

using namespace std;


enum Key {
    TRUCK, 
    BUS, 
    PASSENGER_CAR 
};


struct Car {
    Key K; 
};


Car* In_Car(ifstream& ifst);


void Out_Car(Car* C, ofstream& ofst);


double Load_to_capacity_ratio(Car* C);


struct Truck {
    Key K; 
    int Motor_power; 
    int Load_cap; 
    double Fuel; 
};


Truck* In_Truck(ifstream& ifst);


void Out_Truck(Truck* T, ofstream& ofst);


double Load_to_capacity_ratio_Truck(Truck* T);


struct Bus {
    Key K; 
    int Motor_power; 
    short int Passenger_cap; 
    double Fuel; 
};


Bus* In_Bus(ifstream& ifst);


void Out_Bus(Bus* B, ofstream& ofst);


double Load_to_capacity_ratio_Bus(Bus* B);


struct Passenger_car {
    Key K; 
    int Motor_power; 
    short int Max_speed; 
    double Fuel; 
};


Passenger_car* In_Passenger_car(ifstream& ifst);


void Out_Passenger_car(Passenger_car* P_c, ofstream& ofst);


double Load_to_capacity_ratio_Passenger_car(Passenger_car* P_c);


struct Container {
    int Len; 
    Car* Cont; 
    Container* Prev; 
    Container* Next; 
};

void Init_Container(Container* Head, Container* Tail);

void In_Container(Container* Head, Container* Tail, ifstream& ifst);

void Out_Container(Container* Head, ofstream& ofst);

void Clear_Container(Container* Head, Container* Tail);

bool Compare(Container* First, Container* Second);

void Sort(Container* Head);

void Out_Only_Truck(Container* Head, ofstream& ofst);

#endif //CONTAINER_H