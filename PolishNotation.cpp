// Polska.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>

using namespace std;

void convertToPolish(char *, char *);
bool isCorrect(char *, double *);
void setValue(char *, double *);
double CalcRez(char *, double *);

struct Stack 
{
	char inf;			// Символ операции
	Stack *next;		// Указатель на следующий элемент
};

Stack* push(Stack *t, double s)	//Добавление элемента в стек
{
	Stack *t1 = new Stack;
	t1->inf = s;
	t1->next = t;
	return t1;
}

Stack* pop(Stack *t, double &s)	//Удаление элемента стека 
{
	Stack *t1 = t;
	s = t->inf;
	t = t->next;
	delete t1;
	return t;	//Значение убранного элемента возвращается
}

int Prior(char a)	//Возвращает приоритет операции а
{		
	switch (a) 
	{
	case '^': return 4;
	case '*': 	case '/': 	return 3;
	case '-': 	case '+': 	return 2;
	case '(':   return 1;
	}
	return 0;
}

void main() 
{	
	//setlocale(0, "");
	setlocale(LC_ALL, "Russian");

	char input[50], output[50];	//Входная и выходная строки
	double mas[27] = {};	//Массив под операнды (26 букв английского алфавита)

	cout<<"Введите формулу : "<<endl;  
	cin >> input;

	if (isCorrect(input, mas)) //Correct вернёт true, если входная строка корректна для вычислений
	{ 
		convertToPolish(input, output);
		cout << "Польская запись: " << output << endl;
		setValue(input, mas);
		cout << "Ответ: " << CalcRez(output, mas) << endl;
	}
	system("pause");
}

bool isCorrect(char *input, double *arr)
{
	Stack *brackets = NULL; //Стек для хранения открывающих скобок
	double t;
	char operationsSigns[] = "+-^/*";
	for (int i = 0; i < strlen(input); i++)
	{
		if (isdigit(input[i]))	//если цифра
		{
			cout << "Ошибка! Цифры недопускаются." << endl;
			return false;
		}
		if (ispunct(input[i]) && !strchr(operationsSigns, input[i]) && input[i] != '(' && input[i] != ')')	//если символ не является знаком операции и не скобка
		{
			cout << "Ошибка! Использованы неверные символы." << endl;
			return false;
		}
		if (strchr(operationsSigns, input[i]) && input[i + 1] == NULL) 
		{
			cout << "Ошибка! Знак операции в конце строки." << endl;
			return false;
		}
		if (strchr(operationsSigns, input[i]) && input[i + 1] == '-' && input[i + 2] && isalpha(input[i + 2])) //если перед операндом унарный минус (операнд - отрицательное число)
		{	
			arr[(int)input[i+2] - 97] = -1;
			
			i++;	//пропускаем минус 
			continue;
		}
		if (input[i] == '(')
		{
			brackets = push(brackets, '('); //открывающую скобку добавляем в стек
			continue;
		}
		if (input[i] == ')' && isalpha(input[i + 1]))
		{
			cout << "Операнд после скобки." << endl;
			return false;
		}
		if (isalpha(input[i]) && input[i + 1] == '(')
		{
			cout << "Операнд перед скобкой." << endl;
			return false;
		}
		if (input[i] == ')')
		{
			if (brackets != NULL)
			{
				brackets = pop(brackets, t); //как только найдена закрывающая скобка - удаляем соответствующую открывающую 
				continue;
			}
			else
			{
				cout << "Ошибка в скобках." << endl;
				return false;
			}
		}
		if (isalpha(input[i]) && isalpha(input[i + 1]))
		{
			cout << "Два операнда подряд." << endl;
			return false;
		}
		if (ispunct(input[i]) && ispunct(input[i + 1]) && input[i + 1] != '(')
		{
			cout << "Два оператора подряд." << endl;
			return false;
		}
		
	}
	if (brackets != NULL) //если в стеке остались незакрытые скобки
	{
		cout << "Ошибка в скобках." << endl;
		return false;
	}
}

void convertToPolish(char *input, char *output)
{
	Stack *top = NULL;
	int n = 0; // Итератор	
	double inf;
	for (int i = 0; i < strlen(input); i++)
	{
		_strlwr(input); //Преобразуем строку в нижний регистр
		char ch = input[i]; //Записываем текущий элемент строки в ch
		if (ch >= 'a' && ch <= 'z')
		{
			output[n++] = ch;
			continue;
		}
		if (top == NULL || ch == '(')          //Открывающую скобку записываем в стек
		{
			top = push(top, ch);
			continue;
		}
		if (ch == ')')            // Выталкиваем из стека все знаки операций до открывающей скобки
		{
			while (top->inf != '(')
			{
				top = pop(top, inf);      // Считываем элемент из стека
				output[n++] = (char)inf;         // Записываем в строку
			}
			top = pop(top, inf);               // Удаляем из стека (
			continue;
		}

		/* Если символ – знак операции, переписываем из стека в строку output
		все операции с большим или равным приоритетом */
		int priority = Prior(ch);
		while (top != NULL && Prior((char)top->inf) >= priority)
		{
			top = pop(top, inf);
			output[n++] = (char)inf;
		}
		top = push(top, ch);
	}
	while (top != NULL)	// Если стек не пуст, переписываем все операции в выходную строку
	{
		top = pop(top, inf);
		output[n++] = (char)inf;
	}
	output[n++] = '\0';
}


void setValue(char *input, double *arr)
{
	for (int i = 0; i < strlen(input); i++)
	{
		if ((int)input[i] >= 97 && (int)input[i] <= 122)			
			if (arr[(int)input[i] - 97] == -1) continue;			
			arr[(int)input[i] - 97] = 1;
	}
	for (int i = 0; i <= 26; i++)
	{
		if (arr[i] == 1)
		{
			cout << "Пусть " << (char)(i + 97) << " равно " ;
			cin >> arr[i];
		}
		if (arr[i] == -1) // Если ранее перед операндом был
		{
			cout << "Пусть " << (char)(i + 97) << " равно ";
			cin >> arr[i];
			arr[i] = -arr[i];
		}
	}
}


double CalcRez(char *str, double *mas)
{
	Stack *sp = NULL;
	char ch;
	double	inf, inf1, inf2;
	for (unsigned int i = 0; i<strlen(str); i++)
	{
		ch = str[i];		
		if (ch >= 'a' && ch <= 'z')
		{
			sp = push(sp, mas[int(ch)-97]);
			continue;
		}
		sp = pop(sp, inf2); 
		sp = pop(sp, inf1);
		switch (ch)
		{
		case '+': sp = push(sp, inf1 + inf2); break;
		case '-': sp = push(sp, inf1 - inf2); break;
		case '*': sp = push(sp, inf1 * inf2); break;
		case '^': sp = push(sp, pow(inf1, inf2)); break;
		case '/': 
			if (inf2 == 0) 
			{
				cout << "Ответ - бесконечность. (Деление на ноль)" << endl;
				system("pause");
				exit(1);
			}
			else sp = push(sp, inf1 / inf2); break;
		}
	}
	sp = pop(sp, inf);
	return inf;
}