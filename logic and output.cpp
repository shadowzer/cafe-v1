#include "stdafx.h"
#include "header.h"

void calculation(map <string, double> menu, list <position> kitchen, list<one_check> checks, position* orders)
{
	list<position>::iterator it1 = kitchen.begin();
	while (it1 != kitchen.end())  // в массив добавляем блюда, сделанные на кухне
	{
		unsigned int i = 0;
		while ((i < menu.size()) && (it1->name.compare(orders[i].name)))
		{
			++i;
		}
		if (i != menu.size()) orders[i].count += it1->count;
		++it1;
	}

	list<one_check>::iterator it2 = checks.begin();
	while (it2 != checks.end())  // в массиве вычитаем блюда, оплаченные по чеку
	{
		unsigned int i = 0;
		it1 = it2->positions.begin();
		while (it1 != it2->positions.end())
		{
			i = 0;
			while ((it1->name.compare(orders[i].name)) && (i < menu.size()))
			{
				++i;
			}
			if (i < menu.size()) orders[i].count -= it1->count;
			++it1;
		}
		++it2;
	}
}

double countLoses(position* orders, map<string, double> menu)
{
	double moneyLose = 0;
	for (unsigned int i = 0; i < menu.size(); i++)
	{
		if (!orders[i].count)
		{
			continue;
		}
		if (orders[i].count > 0)
		{
			moneyLose += orders[i].count * menu[orders[i].name];
			continue;
		}
		moneyLose += orders[i].count * (-1) * menu[orders[i].name];
	}
	return moneyLose;
}

void outputLoses(position* orders, map<string, double> menu, double moneyLose)
{
	for (unsigned int i = 0; i < menu.size(); i++)
	{
		if (!orders[i].count)
		{
			continue;
		}
		if (orders[i].count > 0)
		{
			cout << "Блюдо '" << orders[i].name << "' пробито по чеку на " << orders[i].count << " порций меньше, чем сделано на кухне. Потеря = " << orders[i].count * menu[orders[i].name] << " руб." << endl;
			continue;
		}
		cout << "Блюдо '" << orders[i].name << "' пробито по чеку на " << (-1) * orders[i].count << " порций больше, чем сделано на кухне. Потеря = " << orders[i].count * (-1) * menu[orders[i].name] << " руб." << endl;
	}
	if (moneyLose) cout << "\n\nОбщая потеря = " << moneyLose << " руб." << endl;
	else cout << "Кражи не было." << endl;
}

double countWithSales(list<one_check> checks, list<one_check>::iterator it)
{
	return (it->sum * (100 - it->sale) / 100);
}

void outputSum(list<one_check> checks)
{
	for (list<one_check>::iterator it = checks.begin(); it != checks.end(); ++it)
	{
		cout << "Номер чека " << it->number << endl;
		cout << "Сумма без скидки = " << it->sum << endl;
		cout << "Скидка = " << it->sale << "%" << endl;
		cout << "Сумма со скидкой = " << countWithSales(checks, it) << endl;
		cout << endl;
	}

}

void logic(map <string, double> menu, list <position> kitchen, list<one_check> checks, position* orders)
{
	unsigned int i = 0;
	map<string, double>::iterator it = menu.begin();
	while (it != menu.end())  // заполнение меню(блюдо_кол-во_сделанного/оплаченного)
	{
		orders[i].name = it->first;
		orders[i++].count = 0;
		++it;
	}
	
	calculation(menu, kitchen, checks, orders);
	// в результате получаем массив структур, в которых поле count: 1)=0 -> сделано на кухне и проплачено по чеку одинаковое кол-во порций; 2)>0 -> сделано на кухне на n больше, чем проплачено по чеку; 
	// 3)<0 -> проплачено по чеку на n больше, чем сделано на кухне 
}
