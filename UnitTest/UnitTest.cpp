#include "pch.h"
#include "CppUnitTest.h"

#include "../4lab/Header.h"
#include "../4lab/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(In_Truck_Test) //Тест проверки ввода информации о грузовике
		{
			ifstream ifst("../4lab/in_truck.txt");

			Truck* T = In_Truck(ifst);

			Assert::AreEqual(T->Motor_power, 100);
			Assert::AreEqual(T->Load_cap, 1500);
			Assert::AreEqual(T->Fuel, 32.3);
		}
		TEST_METHOD(In_Bus_Test) //Тест проверки ввода информации об автобусе
		{
			ifstream ifst("../4lab/in_bus.txt");

			Bus* B = In_Bus(ifst);

			Assert::AreEqual(B->Motor_power, 110);
			Assert::AreEqual(B->Passenger_cap, (short int)54);
			Assert::AreEqual(B->Fuel, 27.8);
		}
		TEST_METHOD(In_Passenger_car_Test) //Тест проверки ввода информации о легковом автомобиле
		{
			ifstream ifst("../4lab/in_passenger_car.txt");

			Passenger_car* P_c = In_Passenger_car(ifst);

			Assert::AreEqual(P_c->Motor_power, 135);
			Assert::AreEqual(P_c->Max_speed, (short int)330);
			Assert::AreEqual(P_c->Fuel, 17.6);
		}
		TEST_METHOD(In_Car_Test) //Тест проверки ввода информации о машине
		{
			ifstream ifst("../4lab/in_car.txt");

			Car* C = In_Car(ifst);

			Assert::AreEqual((int)C->K, (int)TRUCK);
		}
		TEST_METHOD(Out_Truck_Test) //Тест проверки вывода информации о грузовике
		{
			Truck* T_act = new Truck();

			T_act->Motor_power = 100;
			T_act->Load_cap = 1500;
			T_act->Fuel = 32.3;

			ofstream ofst("../4lab/out_truck_act.txt");

			Out_Truck(T_act, ofst);

			ifstream ifst_exp("../4lab/out_truck_exp.txt");
			ifstream ifst_act("../4lab/out_truck_act.txt");

			string Expected;
			getline(ifst_exp, Expected, '\0');
			string Actual;
			getline(ifst_act, Actual, '\0');

			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(Out_Bus_Test) //Тест проверки вывода информации об автобусе
		{
			Bus* B_act = new Bus();

			B_act->Motor_power = 110;
			B_act->Passenger_cap = 54;
			B_act->Fuel = 27.8;

			ofstream ofst("../4lab/out_bus_act.txt");

			Out_Bus(B_act, ofst);

			ifstream ifst_exp("../4lab/out_bus_exp.txt");
			ifstream ifst_act("../4lab/out_bus_act.txt");

			string Expected;
			getline(ifst_exp, Expected, '\0');
			string Actual;
			getline(ifst_act, Actual, '\0');

			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(Out_Passenger_car_Test) //Тест проверки вывода информации о легковом автомобиле
		{
			Passenger_car* P_c_act = new Passenger_car();

			P_c_act->Motor_power = 135;
			P_c_act->Max_speed = 330;
			P_c_act->Fuel = 17.6;

			ofstream ofst("../4lab/out_passenger_car_act.txt");

			Out_Passenger_car(P_c_act, ofst);

			ifstream ifst_exp("../4lab/out_passenger_car_exp.txt");
			ifstream ifst_act("../4lab/out_passenger_car_act.txt");

			string Expected;
			getline(ifst_exp, Expected, '\0');
			string Actual;
			getline(ifst_act, Actual, '\0');

			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(Out_Car_Test) //Тест проверки вывода информации о машине
		{
			Passenger_car* P_c_act = new Passenger_car();

			P_c_act->Motor_power = 135;
			P_c_act->Max_speed = 330;
			P_c_act->Fuel = 17.6;

			Car* C_act = (Car*)P_c_act;

			C_act->K = PASSENGER_CAR;

			ofstream ofst("../4lab/out_car_act.txt");

			Out_Car(C_act, ofst);

			ifstream ifst_exp("../4lab/out_car_exp.txt");
			ifstream ifst_act("../4lab/out_car_act.txt");

			string Expected;
			getline(ifst_exp, Expected, '\0');
			string Actual;
			getline(ifst_act, Actual, '\0');

			Assert::AreEqual(Expected, Actual);
		}
		TEST_METHOD(Load_to_capacity_ratio_Test) //Тест проверки функции подсчет отношения грузоподъемности к мощности
		{
			Truck* T = new Truck;

			T->Motor_power = 100;
			T->Load_cap = 1500;

			Car* C = (Car*)T;
			C->K = TRUCK;

			double Ratio_exp = 15;
			double Ratio_act = Load_to_capacity_ratio(C);

			Assert::AreEqual(Ratio_exp, Ratio_act);
		}
		TEST_METHOD(Compare_Test) //Тест проверки компаратора
		{
			Passenger_car* P_c_first = new Passenger_car;
			Passenger_car* P_c_second = new Passenger_car;

			P_c_first->Motor_power = 135;
			P_c_second->Motor_power = 140;

			Container* Head_first = new Container;
			Container* Head_second = new Container;
			
			Head_first->Cont = (Car*)P_c_first;
			Head_first->Cont->K = PASSENGER_CAR;

			Head_second->Cont = (Car*)P_c_second;
			Head_second->Cont->K = PASSENGER_CAR;

			bool Act = Compare(Head_first, Head_second);
			bool Exp = true;

			Assert::AreEqual(Exp, Act);
		}
		TEST_METHOD(Sort_Test) //Тест проверки сортировки
		{
			ifstream ifst("../4lab/input.txt");

			Container* Head = new Container();
			Container* Tail = new Container();

			Init_Container(Head, Tail);

			In_Container(Head, Tail, ifst);

			ofstream ofst("../4lab/sort_act.txt");

			Sort(Head);

			Out_Container(Head, ofst);

			ifstream ifst_exp("../4lab/sort_exp.txt");
			ifstream ifst_act("../4lab/sort_act.txt");

			string Exp;
			getline(ifst_exp, Exp, '\0');
			string Act;
			getline(ifst_act, Act, '\0');

			Assert::AreEqual(Exp, Act);
		}
	};
}
