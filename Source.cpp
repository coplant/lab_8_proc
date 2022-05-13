#include "Header.h"
#include <string>

void Init_Container(Container* Head, Container* Tail) {
    Head->Cont = Tail->Cont = NULL;
    Head->Next = Tail->Next = NULL;
    Head->Prev = Tail->Prev = NULL;
    Head->size = Tail->size = 0;
}

void In_Container(Container* Head, Container* Tail, ifstream& ifst) {
    Container* Temp;
    int size = 0;
    while (!ifst.eof()) {
        Temp = new Container();
        Temp->Next = NULL;
        Temp->Prev = NULL;
        if (!size) {
            if ((Head->Cont = In_Car(ifst))) {
                Tail = Head;
                size++;
            }
        }
        else {
            if ((Temp->Cont = In_Car(ifst))) {
                Tail->Next = Temp;
                Temp->Prev = Tail;
                Tail = Temp;
                size++;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        Head->size = size;
        if (Head->Next) {
            Head = Head->Next;
        }
    }
}

void Out_Container(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->size
        << " elements." << endl << endl;

    Container* Temp = Head;
    for (int i = 0; i < Head->size; i++) {
        ofst << i << ": ";
        Out_Car(Temp->Cont, ofst);
        ofst << "Load to capacity ratio is = " << Load_to_capacity_ratio(Temp->Cont) << endl << endl;
        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

void Clear_Container(Container* Head, Container* Tail) {
    Container* Temp = Head;
    for (int i = 0; i < Head->size; i++) {
        free(Temp->Cont);
        Temp->size = 0;
        if (Temp->Next) {
            Temp = Temp->Next;
            free(Temp->Prev);
        }
    }
    Head->size = 0;
}

bool Compare(Container* First, Container* Second) {
    return Load_to_capacity_ratio(First->Cont) > Load_to_capacity_ratio(Second->Cont);
}

void Sort(Container* Head) {
    if (Head->size > 1) {
        Container* First = Head;
        Container* Second = Head->Next;
        Container* Temp = new Container;
        for (int i = 0; i < Head->size - 1; i++) {
            for (int j = 0; j < Head->size - i - 1; j++) {
                if (Compare(First, Second)) {
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

void Out_Only_Truck(Container* Head, ofstream& ofst) {
    ofst << "Only Trucks." << endl << endl;
    Container* Temp = Head;
    for (int i = 0; i < Head->size; i++) {
        if (Temp->Cont->K == TRUCK) {
            ofst << i << ": ";
            Out_Car(Temp->Cont, ofst);
        }
        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

Car* In_Car(ifstream& ifst) {
    Car* C;
    string Temp_Str = "";
    getline(ifst, Temp_Str);

    //Проверка того, что файл либо содержит ошибочный идентификтор Машины,
    //либо не содержит его вовсе
    if ((Temp_Str != "1") && (Temp_Str != "2") && (Temp_Str != "3")) {
        //Возможно идентификатора нет, потому что это конец файл
        if (ifst.peek() == EOF) {
            return 0;
        }
        else { //В ином случае идентификатор отсутствует вовсе, либо он ошибочен - Завершение программы с ошибкой
            cout << "Input data is incomplete or incorrect!";
            exit(1);
        }
    }

    int K = atoi(Temp_Str.c_str());
    if (K == 1) {
        C = (Car*)In_Truck(ifst);
    }
    else if (K == 2) {
        C = (Car*)In_Bus(ifst);
    }
    else if (K == 3) {
        C = (Car*)In_Passenger_car(ifst);
    }
    else {
        return 0;
    }
    return C;
}

void Out_Car(Car* C, ofstream& ofst) {
    if (C->K == TRUCK) {
        Out_Truck((Truck*)C, ofst);
    }
    else if (C->K == BUS) {
        Out_Bus((Bus*)C, ofst);
    }
    else if (C->K == PASSENGER_CAR) {
        Out_Passenger_car((Passenger_car*)C, ofst);
    }
    else {
        ofst << "Incorrect element!" << endl;
    }
}

double Load_to_capacity_ratio(Car* C) {
    if (C->K == TRUCK) {
        return Load_to_capacity_ratio_Truck((Truck*)C);
    }
    else if (C->K == BUS) {
        return Load_to_capacity_ratio_Bus((Bus*)C);
    }
    else if (C->K == PASSENGER_CAR) {
        return Load_to_capacity_ratio_Passenger_car((Passenger_car*)C);
    }
    else {
        return -1;
    }
}

Truck* In_Truck(ifstream& ifst) {
    Truck* T = new Truck();
    string Temp_Str = "";
    string Alph_num = "0123456789";

    getline(ifst, Temp_Str);
    if (Temp_Str == "") { //Если строка пустая или начинается с 0 - ошибка
        cout << "Input data is incomplete!";
        exit(1);
    }
    if (Temp_Str[0] == '0') {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            cout << "Input data is incorrect!";
            exit(1);
        }
    }
    T->Motor_power = atoi(Temp_Str.c_str());

    getline(ifst, Temp_Str);
    if (Temp_Str == "") { //Если строка пустая или начинается с 0 - ошибка
        cout << "Input data is incomplete!";
        exit(1);
    }
    if (Temp_Str[0] == '0') {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
    }
    T->Load_cap = atoi(Temp_Str.c_str());

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }
    //Проверка того, что строка не начианется с 0, точки или запятой, а также не заканчивается точкой или запятой
    if ((Temp_Str[0] == 0) || (Temp_Str[0] == ',') || (Temp_Str[0] == '.') ||
        (Temp_Str[Temp_Str.sizegth() - 1] == ',') || (Temp_Str[Temp_Str.sizegth() - 1] == '.')) {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл провреки корректности записи вещественного числа
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if ((Alph_num.find(Temp_Str[i]) == -1) && (Temp_Str[i] != ',') && (Temp_Str[i] != '.')) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }

        if ((Temp_Str[i] == ',') || (Temp_Str[i] == '.')) {
            if ((Temp_Str[i - 1] == ',') || (Temp_Str[i - 1] == '.') ||
                (Temp_Str[i + 1] == ',') || (Temp_Str[i + 1] == '.')) {
                cout << "Input data is incorrect!";
                exit(1);
            }
        }
    }
    T->Fuel = strtod(Temp_Str.c_str(), NULL);
    return T;
}


void Out_Truck(Truck* T, ofstream& ofst) {
    ofst << "It's a Truck with motor power = " << T->Motor_power << endl;
    ofst << "Its load capacity is " << T->Load_cap << endl;
    ofst << "Its fuel is " << T->Fuel << endl;
}

double Load_to_capacity_ratio_Truck(Truck* T) {
    return (double)T->Load_cap / (double)T->Motor_power;
}

Bus* In_Bus(ifstream& ifst) {
    Bus* B = new Bus();
    string Temp_Str = "";
    string Alph_num = "0123456789";

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }
    if (Temp_Str[0] == '0') {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            cout << "Input data is incorrect!";
            exit(1);
        }
    }
    B->Motor_power = atoi(Temp_Str.c_str());

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }
    if (Temp_Str[0] == '0') {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
    }
    B->Passenger_cap = atoi(Temp_Str.c_str());

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }

    //Проверка того, что строка не начианется с 0, точки или запятой, а также не заканчивается точкой или запятой
    if ((Temp_Str[0] == 0) || (Temp_Str[0] == ',') || (Temp_Str[0] == '.') ||
        (Temp_Str[Temp_Str.sizegth() - 1] == ',') || (Temp_Str[Temp_Str.sizegth() - 1] == '.')) {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл провреки корректности записи вещественного числа
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if ((Alph_num.find(Temp_Str[i]) == -1) && (Temp_Str[i] != ',') && (Temp_Str[i] != '.')) {
            cout << "Input data is incorrect!";
            exit(1);
        }
        if ((Temp_Str[i] == ',') || (Temp_Str[i] == '.')) {
            if ((Temp_Str[i - 1] == ',') || (Temp_Str[i - 1] == '.') ||
                (Temp_Str[i + 1] == ',') || (Temp_Str[i + 1] == '.')) {
                cout << "Input data is incorrect!";
                exit(1);
            }
        }
    }
    B->Fuel = strtod(Temp_Str.c_str(), NULL);
    return B;
}

void Out_Bus(Bus* B, ofstream& ofst) {
    ofst << "It's a Bus with motor power = " << B->Motor_power << endl;
    ofst << "Its passenger capacity is " << B->Passenger_cap << endl;
    ofst << "Its fuel is " << B->Fuel << endl;
}

double Load_to_capacity_ratio_Bus(Bus* B) {
    return (double)(75 * B->Passenger_cap) / (double)B->Motor_power;
}

Passenger_car* In_Passenger_car(ifstream& ifst) {
    Passenger_car* P_c = new Passenger_car();
    string Temp_Str = "";
    string Alph_num = "0123456789";

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }
    if (Temp_Str[0] == '0') {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            cout << "Input data is incorrect!";
            exit(1);
        }
    }
    P_c->Motor_power = atoi(Temp_Str.c_str());

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }
    if (Temp_Str[0] == '0') {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            cout << "Input data is incorrect!";
            exit(1);
        }
    }
    P_c->Max_speed = atoi(Temp_Str.c_str());

    getline(ifst, Temp_Str);
    if (Temp_Str == "") {
        cout << "Input data is incomplete!";
        exit(1);
    }

    //Проверка того, что строка не начианется с 0, точки или запятой, а также не заканчивается точкой или запятой
    if ((Temp_Str[0] == 0) || (Temp_Str[0] == ',') || (Temp_Str[0] == '.') ||
        (Temp_Str[Temp_Str.sizegth() - 1] == ',') || (Temp_Str[Temp_Str.sizegth() - 1] == '.')) {
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл провреки корректности записи вещественного числа
    for (int i = 0; i < Temp_Str.sizegth(); i++) {
        if ((Alph_num.find(Temp_Str[i]) == -1) && (Temp_Str[i] != ',') && (Temp_Str[i] != '.')) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
        if ((Temp_Str[i] == ',') || (Temp_Str[i] == '.')) {
            if ((Temp_Str[i - 1] == ',') || (Temp_Str[i - 1] == '.') ||
                (Temp_Str[i + 1] == ',') || (Temp_Str[i + 1] == '.')) {
                cout << "Input data is incorrect!";
                exit(1);
            }
        }
    }
    P_c->Fuel = strtod(Temp_Str.c_str(), NULL);
    return P_c;
}

void Out_Passenger_car(Passenger_car* P_c, ofstream& ofst) {
    ofst << "It's a Passenger car with motor power = " << P_c->Motor_power << endl;
    ofst << "Its Max speed is " << P_c->Max_speed << endl;
    ofst << "Its fuel is " << P_c->Fuel << endl;
}

double Load_to_capacity_ratio_Passenger_car(Passenger_car* P_c) {
    return (double)(75 * 4) / (double)P_c->Motor_power; //4 пассажирских места для людей по 75 кг
}