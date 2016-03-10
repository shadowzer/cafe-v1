#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream> 
#include <map>
#include <list>

using namespace std;

typedef struct _position
{
	string name;
	int count;
} position;

typedef struct _one_check
{
	int number;
	list <position> positions;
	double sum;
	int sale;
} one_check;

map <string, double> input_menu();
list <position> input_kitchen(map <string, double> menu);
list<one_check> input_check(map <string, double> menu);

void string_ckecker(string name_dish);
void isNumberPositive(int num);
void isNumberPositive(double num);
void isSumCorrect(one_check check, map<string, double> menu);

void logic(map <string, double> menu, list <position> kitchen, list<one_check> checks, position* orders);
double countLoses(position* orders, map<string, double> menu);
void outputLoses(position* orders, map<string, double> menu, double moneyLose);
double countWithSales(list<one_check> checks, list<one_check>::iterator it);
void outputSum(list<one_check> checks);
