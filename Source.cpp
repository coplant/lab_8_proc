#include "Header.h"

void Init_Container(Container* Head, Container* Tail) {
    Head->Cont = Tail->Cont = NULL;
    Head->Next = Tail->Next = NULL; 
    Head->Prev = Tail->Prev = NULL;
    Head->Len = Tail->Len = 0;
}

void In_Container(Container* Head, Container* Tail, ifstream& ifst) {
    Container* Temp;
    int Len = 0; //Переменная для подсчета числа элементов контейнера

    while (!ifst.eof()) {
        Temp = new Container(); 
        Temp->Next = NULL;
        Temp->Prev = NULL;
        
        if (!Len) {
            if ((Head->Cont = In_Car(ifst))) {
                Tail = Head;
                Len++;
            }
        }
        else {
            if ((Temp->Cont = In_Car(ifst))) {
                Tail->Next = Temp;
                Temp->Prev = Tail;
                Tail = Temp;
                Len++;
            }
        }
    }

    //Записываем размерность контейнера в каждом узле
    for (int i = 0; i < Len; i++) {
        Head->Len = Len;
        if (Head->Next) {
            Head = Head->Next;
        }
    }
}

void Out_Container(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->Len
        << " elements." << endl << endl;

    Container* Temp = Head; //Временно указываем на адрес первого элемента

    for (int i = 0; i < Head->Len; i++) {
        ofst << i << ": ";
        Out_Car(Temp->Cont, ofst);

        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

void Clear_Container(Container* Head, Container* Tail) {
    Container* Temp = Head;
    
    for (int i = 0; i < Head->Len; i++) {
        free(Temp->Cont);
        Temp->Len = 0;
        
        if (Temp->Next) {
            Temp = Temp->Next;
            free(Temp->Prev);
        }

    }

    Head->Len = 0;
}

void Out_Only_Truck(Container* Head, ofstream& ofst) {
    ofst << "Only Trucks." << endl << endl;

    Container* Temp = Head; //Временно указываем на адрес первого элемента

    for (int i = 0; i < Head->Len; i++) {
        if (Temp->Cont->K == TRUCK) { //Проверка того, что машина - грузовик
            ofst << i << ": ";
            Out_Car(Temp->Cont, ofst);
        }

        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

Car* In_Car(ifstream& ifst) {
    Car* C; //Создаем указатель на машину
    int K;

    ifst >> K; //Считываем идентификатор 

    if (K == 1) {
       
        C = (Car*)In_Truck(ifst); //Считываем информацию о грузовике

        C->K = TRUCK; //Записываем тип машины

        return C;
    }
    else if (K == 2) {
        C = (Car*)In_Bus(ifst); //Считываем информацию об автобусе

        C->K = BUS; //Записываем тип машины

        return C;
    }
    else {
        return 0;
    }
}

void Out_Car(Car* C, ofstream& ofst) {
    if (C->K == TRUCK) {
        Out_Truck((Truck*)C, ofst); //Вывод грузовика
    }
    else if (C->K == BUS) {
        Out_Bus((Bus*)C, ofst); //Вывод автобуса
    }
    else {
        ofst << "Incorrect element!" << endl;
    }
}

Truck* In_Truck(ifstream& ifst) {
    Truck* T = new Truck();

    ifst >> T->Motor_power;
    ifst >> T->Load_cap;

    return T;
}


void Out_Truck(Truck* T, ofstream& ofst) {
    ofst << "It's a Truck with motor power = " << T->Motor_power<< endl;
    ofst << "Its load capacity is " << T->Load_cap << endl << endl;
}

Bus* In_Bus(ifstream& ifst) {
    Bus* B = new Bus();

    ifst >> B->Motor_power;
    ifst >> B->Passenger_cap;

    return B;
}

void Out_Bus(Bus* B, ofstream& ofst) {
    ofst << "It's a Bus with motor power = " << B->Motor_power << endl;
    ofst << "Its passenger capacity is " << B->Passenger_cap << endl << endl;
}