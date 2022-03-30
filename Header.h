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


struct Truck {
    Key K; 
    int Motor_power; 
    int Load_cap; 
    double Fuel; 
};


Truck* In_Truck(ifstream& ifst);


void Out_Truck(Truck* T, ofstream& ofst);


struct Bus {
    Key K; 
    int Motor_power;                       
    short int Passenger_cap; 
    double Fuel; 
};


Bus* In_Bus(ifstream& ifst);


void Out_Bus(Bus* B, ofstream& ofst);


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