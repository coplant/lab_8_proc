#include "Header.h"

Container::Container() {
    Head = Tail = new Node();
    Head->Cont = Tail->Cont = NULL;
    Head->Next = Tail->Next = NULL;
    Head->Prev = Tail->Prev = NULL;
    Len = 0;
}

void Container::In(ifstream& ifst) {
    Node* Temp;

    while (!ifst.eof()) {
        Temp = new Node(); //Создаем новый узел
        //Инициализируем новый узел
        Temp->Next = NULL;
        Temp->Prev = NULL;

        
        if (!Len) { //Запись 1-го элемента
            if ((Head->Cont = Car::In_Car(ifst))) {
                Tail = Head;
                Len++;
            }
        }
        else { //Запись последующих элементов
            if ((Temp->Cont = Car::In_Car(ifst))) {
                Tail->Next = Temp;
                Temp->Prev = Tail;
                Tail = Temp;
                Len++;
            }
        }
    }
}

void Container:: Out(ofstream& ofst) {
    ofst << "Container contains " << Len
        << " elements." << endl << endl;

    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        ofst << i << ": ";
        Temp->Cont->Out_Data(Temp->Cont->Get_Motor_power(), Temp->Cont->Get_Fuel(), ofst);

        ofst << "Load to capacity ratio is = " << Temp->Cont->Load_to_capacity_ratio(Temp->Cont->Get_Motor_power()) << endl << endl;

        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

void Container::Clear() {
    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        free(Temp->Cont);

        if (Temp->Next) {
            Temp = Temp->Next;
            free(Temp->Prev);
        }

    }

    Len = 0;
}

void Container::Sort() {
    if (Len > 1) {
        Node* First = Head;
        Node* Second = Head->Next;
        Node* Temp = new Node;

        for (int i = 0; i < Len - 1; i++) {
            for (int j = 0; j < Len - i - 1; j++) {
                if (First->Cont->Compare(Second->Cont)) {
                    Temp->Cont = First->Cont;
                    First->Cont = Second->Cont;
                    Second->Cont = Temp->Cont;
                }

                Second = Second->Next;
            }

            First = First->Next;
            Second = First->Next;
        }
    }
}

void Container::Out_Only_Truck(ofstream& ofst) {
    ofst << "Only Trucks." << endl << endl;

    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        ofst << i << ": ";
        Temp->Cont->Out_Only_Truck(Temp->Cont->Get_Motor_power(), Temp->Cont->Get_Fuel(), ofst);

        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

void Container::Set_Head(Node* _Head) {
    Head = _Head;
}
Node* Container::Get_Head() {
    return Head;
}

void Container::Set_Tail(Node* _Tail) {
    Tail = _Tail;
}
Node* Container::Get_Tail() {
    return Tail;
}

void Container::Set_Len(int _Len) {
    Len = _Len;
}
int Container::Get_Len() {
    return Len;
}

Car* Car::In_Car(ifstream& ifst) {
    Car* C;
    int K;

    ifst >> K;
    
    if (K == 1) {
        C = new Truck;
    }
    else if (K == 2) {
        C = new Bus;
    }
    else if (K == 3) {
        C = new Passenger_car;
    }
    else {
        return 0;
    }

    ifst >> C->Motor_power; //Cчитываем мощность мотора

    C->In_Data(ifst);

    ifst >> C->Fuel; //Считываем расход топлива

    return C;
}

void Car::Set_Motor_power(int _Motor_power) {
    Motor_power = _Motor_power;
}

int Car::Get_Motor_power() {
    return Motor_power;
}

void Car::Set_Fuel(double _Fuel) {
    Fuel = _Fuel;
}

double Car::Get_Fuel() {
    return Fuel;
}

bool Car::Compare(Car* Other) {
    return Load_to_capacity_ratio(Motor_power) > Other->Load_to_capacity_ratio(Other->Get_Motor_power());
}

void Car::Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << endl;
}

void Truck::In_Data(ifstream& ifst) {
    ifst >> Load_cap;
}

void Truck::Out_Data(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << "It's a Truck with motor power = " << Motor_power << endl;
    ofst << "Its load capacity is " << Load_cap << endl;
    ofst << "Its fuel is " << Fuel << endl;
}

double Truck::Load_to_capacity_ratio(int Motor_power) {
    return (double)Load_cap / (double)Motor_power;
}

void Truck::Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst) {
    Out_Data(Motor_power, Fuel, ofst);
}

void Truck::Set_Load_cap(int _Load_cap) {
    Load_cap = _Load_cap;
}

int Truck::Get_Load_cap() {
    return Load_cap;
}

void Bus::In_Data(ifstream& ifst) {
    ifst >> Passenger_cap;
}

void Bus::Out_Data(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << "It's a Bus with motor power = " << Motor_power << endl;
    ofst << "Its passenger capacity is " << Passenger_cap << endl;
    ofst << "Its fuel is " << Fuel << endl;
}

double Bus::Load_to_capacity_ratio(int Motor_power) {
    return (double)(75 * Passenger_cap) / (double)Motor_power;
}

void Bus::Set_Passenger_cap(short int _Passenger_cap) {
    Passenger_cap = _Passenger_cap;
}

short int Bus::Get_Passenger_cap() {
    return Passenger_cap;
}

void Passenger_car::In_Data(ifstream& ifst) {
    ifst >> Max_speed;
}

void Passenger_car::Out_Data(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << "It's a Passenger car with motor power = " << Motor_power << endl;
    ofst << "Its Max speed is " << Max_speed << endl;
    ofst << "Its fuel is " << Fuel << endl;
}

double Passenger_car::Load_to_capacity_ratio(int Motor_power) {
    return (double)(75 * 4) / (double)Motor_power; //4 пассажира по 75 кг
}

void Passenger_car::Set_Max_speed(short int _Max_speed) {
    Max_speed = _Max_speed;
}

short int Passenger_car::Get_Max_speed() {
    return Max_speed;
}