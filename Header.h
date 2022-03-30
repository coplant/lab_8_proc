#ifndef CONTAINER_H
#define CONTAINER_H

#include <fstream>

using namespace std;


enum Key {
    TRUCK, 
    BUS 
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
};


Truck* In_Truck(ifstream& ifst);


void Out_Truck(Truck* T, ofstream& ofst);


double Load_to_capacity_ratio_Truck(Truck* T);


struct Bus {
    Key K; 
    int Motor_power; 
    short int Passenger_cap; 
};

Bus* In_Bus(ifstream& ifst);


void Out_Bus(Bus* B, ofstream& ofst);

double Load_to_capacity_ratio_Bus(Bus* B);


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

#endif //CONTAINER_H