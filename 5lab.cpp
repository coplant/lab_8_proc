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
    if (!ifst.is_open()) {
        cout << "No input file found or could not open!" << endl;
        system("pause");
        return 1;
    }

    ofstream ofst(argv[2]);
    if (!ofst.is_open()) {
        cout << "No output file found or could not open!" << endl;
        system("pause");
        return 1;
    }

    cout << "Start" << endl;
    Container* Head = new Container();
    Container* Tail = new Container();
    Init_Container(Head, Tail);
    In_Container(Head, Tail, ifst);

    ofst << "Filled and sorted container. " << endl;
    Sort(Head);
    Out_Container(Head, ofst);
    Out_Only_Truck(Head, ofst);
    Clear_Container(Head, Tail);

    ofst << "Empty container. " << endl;
    Out_Container(Head, ofst);

    cout << "Stop" << endl;
    system("pause");
    return 0;
}
