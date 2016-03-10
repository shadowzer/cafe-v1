#include "stdafx.h"
#include "header.h"

using namespace std;

void string_ckecker(string name_dish)
{
	if ((name_dish.find('=') == -1) || ((name_dish[name_dish.size() - 1])<'0') || ((name_dish[name_dish.size() - 1])>'9')) // что за 2 и 3 проверки??
	{
		cout << "Ошибка формата файла." << endl;
		system("pause");
		exit(-1);
	}
}

void isNumberPositive(int num)
{
	if (num < 0)
	{
		cout << "Найдено отрицательное число. Ни одно число не может быть отрицательным." << endl;
		system("pause");
		exit(-1);
	}
}

void isNumberPositive(double num)
{
	if (num < 0)
	{
		cout << "Найдено отрицательное число. Ни одно число не может быть отрицательным." << endl;
		system("pause");
		exit(-1);
	}
}

void isSumCorrect(one_check check, map<string, double> menu)
{
	double ctrlSum = 0;
	for (list<position>::iterator it = check.positions.begin(); it != check.positions.end(); ++it)
	{
		ctrlSum += it->count * menu[it->name];
	}
	if (ctrlSum != check.sum)
	{
		cout << "В заказе #" << check.number << " неверно посчитана сумма заказа.\nПробито " << check.sum << "руб.\nРеальная стоимость заказа " << ctrlSum << "руб." << endl;
		system("pause");
		exit(-1);
	}
}

map <string, double> input_menu()
{
	map <string, double> menu;
	map <string, double>::iterator iter;
	string file_name, name_dish;
	int count;
	double price;
	cout << "Введите имя файла меню." << endl;
	cin >> file_name;
	ifstream fin(file_name);
	if (!fin.is_open())
	{
		cout << "Файл меню не найден." << endl;
		system("pause");
		exit(-1);
	}
	while (!fin.eof())//чтение менюшки
	{
		getline(fin, name_dish);  // получает строку типа "имя блюда кол-во"
		string_ckecker(name_dish);
		price = stod(name_dish.substr(name_dish.find_last_of(' = '))); // отрезает число в конце и переводит его в double
		isNumberPositive(price);
		name_dish = name_dish.substr(0, -2 + name_dish.find_last_of(' '));//отрезает число в конце и оставляет строчку
		if (((name_dish.find_last_not_of(" ")) == -1) || (name_dish.find("=") == 0))
		{
			cout << "Отсутствует наименование блюда в меню." << endl;
			system("pause");
			exit(-1);
		}
		iter = menu.find(name_dish);
		if (iter == menu.end())
		{
			menu[name_dish] = price;
		}
		else
		{
			cout << "Дублируется наименование в меню." << endl;
			system("pause");
			exit(-1);
		}
	}
	fin.close();
	return menu;
}
list <position> input_kitchen(map <string, double> menu)
{
	list <position> kitchen;
	string file_name;
	int count;
	double price;
	ifstream fin;
	cout << "Введите имя файла кухни." << endl;
	cin >> file_name;
	fin.open(file_name);
	position pos;
	bool flag;
	if (!fin.is_open())
	{
		cout << "Файл кухни не найден." << endl;
		system("pause");
		exit(-1);
	}
	while (!fin.eof())
	{
		flag = 0;
		getline(fin, pos.name);  // получает строку типа "имя блюда кол-во"
		string_ckecker(pos.name);
		pos.count = stoi(pos.name.substr(pos.name.find_last_of(' = '))); // отрезает число в конце и переводит его в инт
		isNumberPositive(pos.count);
		pos.name = pos.name.substr(0, -2 + pos.name.find_last_of(' '));//отрезает число в конце и оставляет строчку
		if (menu.find(pos.name) == menu.end())
		{
			cout << "Ошибка структуры файла." << endl;
			system("pause");
			exit(-1);
		}
		if (kitchen.empty())
		{
			kitchen.push_front(pos);
		}
		else
		{
			for (std::list<position>::iterator it = kitchen.begin(); it != kitchen.end(); ++it)
			{
				if ((*it).name == pos.name)
				{
					(*it).count = (*it).count + pos.count;
					flag = 1;//если мы вставили элемент он для нас стал 1
				}
			}
			if (!flag)
			{
				kitchen.push_front(pos);
			}
		}
	}
	fin.close();
	return kitchen;
}
list<one_check> input_check(map <string, double> menu)
{
	list<one_check> checks;
	string file_name;
	ifstream fin;
	bool flag;
	position pos;
	cout << "Введите имя файла кассы." << endl;
	cin >> file_name;
	fin.open(file_name);

	if (!fin.is_open())
	{
		cout << "Файл меню не найден." << endl;
		system("pause");
		exit(-1);
	}

	one_check check;
	list<one_check>::iterator it;
	while (!fin.eof())
	{
		flag = 0;
		getline(fin, pos.name);
		check.number = stoi(pos.name.substr(1 + pos.name.find_last_of('№'))); // отрезает число в конце и переводит его в инт
		isNumberPositive(check.number);

		getline(fin, pos.name);
		while ((pos.name.find("итого")) == -1)
		{ //чтение позиций
			string_ckecker(pos.name);
			pos.count = stoi(pos.name.substr(pos.name.find_last_of(' = '))); // отрезает число в конце и переводит его в инт
			isNumberPositive(pos.count);
			pos.name = pos.name.substr(0, -2 + pos.name.find_last_of(' = '));//отрезает число в конце и оставляет строчку
			if (menu.find(pos.name) == menu.end())
			{
				cout << "Ошибка структуры файла." << endl;
				system("pause");
				exit(-1);
			}
			check.positions.push_front(pos);
			getline(fin, pos.name);  // получает строку типа "имя блюда кол-во"
		}

		check.sum = stod(pos.name.substr(pos.name.find_last_of(' ')));
		isNumberPositive(check.sum);
		isSumCorrect(check, menu);
		getline(fin, pos.name);
		if (pos.name.find("====")==-1)
		   {
			   pos.count = stoi(pos.name.substr(pos.name.find_last_of(' '))); 
			   check.sale = pos.count;
			   getline(fin, pos.name);
		   }
		else
		{
			check.sale = 0;
		}
		
		checks.push_front(check);
		check.positions.clear();
	}
	fin.close();
	return checks;
}
