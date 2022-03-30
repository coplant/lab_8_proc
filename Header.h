#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Car {
    int Motor_power; 
    double Fuel; 
public:
    int Get_Motor_power();
    double Get_Fuel();

    static Car* In_Car(ifstream& ifst); 
    virtual void In_Data(ifstream& ifst) = 0; 
                                              
                                              
    virtual void Out_Data(int Motor_power, double Fuel, ofstream& ofst) = 0; 
    virtual double Load_to_capacity_ratio(int Motor_power) = 0; 
    bool Compare(Car* Other); 
    virtual void Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst);
protected:
    Car() {};
};


class Truck : public Car {
    int Load_cap; 
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, double Fuel, ofstream& ofst); 
    double Load_to_capacity_ratio(int Motor_power); 
    void Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst); 
    Truck() {};
};


class Bus : public Car {
    short int Passenger_cap;
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, double Fuel, ofstream& ofst); 
    double Load_to_capacity_ratio(int Motor_power); 
    Bus() {};
};


class Passenger_car : public Car {
    short int Max_speed; 
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, double Fuel, ofstream& ofst);
    double Load_to_capacity_ratio(int Motor_power); 
    Passenger_car() {};
};


struct Node {
    Node* Next, * Prev; 
    Car* Cont; 
};


class Container {
    Node* Head, *Tail; 
    int Len; 
public:
    void In(ifstream& ifst); 
    void Out(ofstream& ofst); 
    void Clear(); 
    void Sort(); 
    void Out_Only_Truck(ofstream& ofst); 
    Container(); 
    ~Container() { Clear(); }
};

#endif //HEADER_H