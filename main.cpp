// cafe_finale.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "header.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	map <string, double> menu = input_menu();
	list <position> kitchen = input_kitchen(menu);
	list<one_check> checks = input_check(menu);

	position* orders = new position[menu.size()];
	logic(menu, kitchen, checks, orders);
	outputLoses(orders, menu, countLoses(orders, menu));
	cout << endl;
	outputSum(checks);
	
	delete[] orders;
	system("pause");
	return 0;
}

