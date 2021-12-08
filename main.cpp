#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <locale.h>
#include <windows.h>
#include <limits.h>
#include "time.h"
#include <ctime>



struct credit // собственно говоря сама структура credit со следующими полями:
{
	int number;
	char *surname;
	char *name;
	double sum;
	int percent;
};
void AddNew(credit**, short*);
void INFOklient(credit*, short);
void INFOschet(credit*, short);
void Procent(credit*, short);
void Exit(credit**);
short qqs(int, credit*, short);

void Procent(credit *ALL, short numOfAccs) //функция поиска  по процентикам )
{
	int percent;
	short n = 0;
	credit *withPercent = (credit*)malloc(n * sizeof(credit));
	printf_s("                                     \n");
	printf_s("      Поиск клинтов по проценту      \n");
	printf_s("- Введите процент                    : ");
	while (scanf_s("%i", &percent) != 1)
	{
		printf_s("- ошибка \n");
		printf_s("- Введите процент: ");
		while (fgetc(stdin) != '\n');
	}
	for (short i = 0; i < numOfAccs; i++)
	{
		if ((*(ALL + i)).percent == percent)
		{
			withPercent = (credit*)realloc(withPercent, ++n * sizeof(credit));
			*(withPercent + n - 1) = *(ALL + i);
		}
	}
	printf_s("                                       \n");
	printf_s("- Клиенты:\n");
	for (short i = 0; i < n; i++)
	{
		printf_s("%hi. %s %s\n", i + 1, (*(withPercent + i)).surname, (*(withPercent + i)).name);
	}
	printf_s("                                     \n\n");
}
void INFOschet(credit *ALL, short numOfAccs) //функция поиск счетов клиента
{
	char surname[255];
	char name[255];
	double sum = 0;
	printf_s("                                     \n");
	printf_s("     Информация о счетах             \n");
	printf_s("- Фамилия клиента:           ");
	scanf_s("%s", surname, sizeof(surname));
	while (fgetc(stdin) != '\n');
	printf_s("-  Имя клиента: ");
	scanf_s("%s", name, sizeof(name));
	while (fgetc(stdin) != '\n');
	printf_s("                                                \n");
	printf_s("Клиенту (%s %s) принадлежат счета: ", surname, name);
	for (int i = 0; i < numOfAccs; i++)
		if (!strcmp((*(ALL + i)).surname, surname) && !strcmp((*(ALL + i)).name, name))
		{
			sum += (*(ALL + i)).sum;
			printf_s("%i ", (*(ALL + i)).number);
		}
	printf("\n- На общую сумму: %.2lf\n", sum);
	printf("                            \n\n");
}
void INFOklient(credit *ALL, short numOfAccs)
{
	int number;
	printf_s("                                     \n");
	printf_s("    Информация о счете               \n");
	printf_s("-      Номер счета:                    ");
	while (scanf_s("%i", &number) != 1)
	{
		printf_s("- ошибка             \n");
		printf_s("- Номер счета:         ");
		while (fgetc(stdin) != '\n');
	}
	short item;
	if ((item = qqs(number, ALL, numOfAccs)) == -1)
	{
		printf_s("-  Счет отсутствует      \n");
		return;
	}
	printf_s("                                        \n");
	printf_s("- Номер счёта: %i\n", number);
	printf_s("- Фамилия клиента: %s\n", (*(ALL + item)).surname);
	printf_s("- Имя клиента: %s\n", (*(ALL + item)).name);
	printf_s("- Сумма: %.2lf\n", (*(ALL + item)).sum);
	printf_s("- Процент: %i\n", (*(ALL + item)).percent);
	printf_s("                                      \n\n");
}
void AddNew(credit **ALL, short *numOfAccs) //функция создания нового счета 
{
	int number;
	char surname[255];
	char name[255];
	double sum;
	int percent;
	printf_s("                                     \n");
	printf_s("- Добавление нового счета -\n");
	printf_s("- Номер счета: ");
	while (short t = scanf_s("%i", &number) != 1 || number < 1 || qqs(number, *ALL, *numOfAccs) != -1)
	{
		if (t != 1 || number < 1)
		{
			printf(" ошибка \n");
		}
		else
		{
			printf_s(" ошибка - такой счет уже существует \n");
		}
		printf_s("                                      \n");
		printf_s("- Номер счета: ");
		while (fgetc(stdin) != '\n');
	}
	printf("- Фамилия клиента- ");
	scanf_s("%s", surname, sizeof(surname));
	while (fgetc(stdin) != '\n');
	printf("- Имя клиента- ");
	scanf_s("%s", name, sizeof(name));
	while (fgetc(stdin) != '\n');
	printf("- Сумма- ");
	while (scanf_s("%lf", &sum) != 1 || sum < 0.0)
	{
		printf("- ошибка \n");
		printf("- Сумма : ");
		while (fgetc(stdin) != '\n');
	}
	printf("- Введите процент: ");
	while (scanf_s("%i", &percent) != 1 || percent < 0)
	{
		printf("- ошибка \n");
		printf("- Введите процент: ");
		while (fgetc(stdin) != '\n');
	}
	*ALL = (credit*)realloc(*ALL, ++(*numOfAccs) * sizeof(credit));
	credit *tmp = *ALL + (*numOfAccs) - 1;
	(*tmp).number = number;
	(*tmp).surname = new char[strlen(surname) + 1];
	strcpy_s((*tmp).surname, strlen(surname) + 1, surname);
	(*tmp).name = new char[strlen(name) + 1];
	strcpy_s((*tmp).name, strlen(name) + 1, name);
	(*tmp).sum = sum;
	(*tmp).percent = percent;
	tmp = NULL;
	printf_s("               Новый счет                   \n");
	printf_s("                                          \n\n");
}
short qqs(int number, credit *ALL, short numOfAccs) {
	int num = -1;
	for (int i = 0; i < numOfAccs; i++)
	{
		if ((*(ALL + i)).number == number)
		{
			num = i;
			break;
		}
	}
	return num;
}
int main(void)
{
	
	SetConsoleCP(1251); //задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	setlocale(LC_ALL, "Russian");
	printf_s(" Реализовать функции:                                                                                                 \n");
	printf_s(" 1.Добавить новый счет                                                                                                   \n");
	printf_s(" 2.Распечатать информацию о счете в табличном виде                                                                       \n");
	printf_s(" 3.Найти все счета  и общую сумму кредитов у заданного клиента (клиент – это фамилия + имя), результат вывести на экран  \n");
	printf_s(" 4.Определить всех клиентов с заданным процентом по кредиту, результат запомнить в массиве и вывести на экран;           \n");

	
	short numOfAccs = 0;
	credit *ALL = (credit*)malloc(numOfAccs * sizeof(credit));
	while (true)
	{
		short item = 0;
		printf_s("|                                     |\n");
		printf_s("|- Добавить новый счет             1 -|\n");
		printf_s("|- Информация о счете              2 -|\n");
		printf_s("|- Поиск счетов клиента            3 -|\n");
		printf_s("|- Поиск клиентов по проценту      4 -|\n");
		printf_s("|- Выход из программы              5 -|\n");
		printf_s("|                                     |\n");
		printf_s("- Введите номер функции: ");
		while (scanf_s("%hi", &item) != 1 || item > 5 || item < 1) {
			printf_s("- ошибка|\n");
			printf_s("                          \n");
			printf_s("- Введите номер функции: ");
			while (fgetc(stdin) != '\n');
		}
		printf_s("                                   \n\n");
		switch (item)
		{
		case 1:
			AddNew(&ALL, &numOfAccs);
			break;
		case 2:
			INFOklient(ALL, numOfAccs);
			break;
		case 3:
			INFOschet(ALL, numOfAccs);
			break;
		case 4:
			Procent(ALL, numOfAccs);
			break;
		case 5:
			exit(0);
		}

	}
	return 0;
}
void Exit(credit **ALL)
{
	free(*ALL);
	exit(0);
}