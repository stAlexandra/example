// Polska.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	char inf;			// ������ ��������
	Stack *next;		// ��������� �� ��������� �������
};

Stack* push(Stack *t, double s)	//���������� �������� � ����
{
	Stack *t1 = new Stack;
	t1->inf = s;
	t1->next = t;
	return t1;
}

Stack* pop(Stack *t, double &s)	//�������� �������� ����� 
{
	Stack *t1 = t;
	s = t->inf;
	t = t->next;
	delete t1;
	return t;	//�������� ��������� �������� ������������
}

int Prior(char a)	//���������� ��������� �������� �
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

	char input[50], output[50];	//������� � �������� ������
	double mas[27] = {};	//������ ��� �������� (26 ���� ����������� ��������)

	cout<<"������� ������� : "<<endl;  
	cin >> input;

	if (isCorrect(input, mas)) //Correct ����� true, ���� ������� ������ ��������� ��� ����������
	{ 
		convertToPolish(input, output);
		cout << "�������� ������: " << output << endl;
		setValue(input, mas);
		cout << "�����: " << CalcRez(output, mas) << endl;
	}
	system("pause");
}

bool isCorrect(char *input, double *arr)
{
	Stack *brackets = NULL; //���� ��� �������� ����������� ������
	double t;
	char operationsSigns[] = "+-^/*";
	for (int i = 0; i < strlen(input); i++)
	{
		if (isdigit(input[i]))	//���� �����
		{
			cout << "������! ����� �������������." << endl;
			return false;
		}
		if (ispunct(input[i]) && !strchr(operationsSigns, input[i]) && input[i] != '(' && input[i] != ')')	//���� ������ �� �������� ������ �������� � �� ������
		{
			cout << "������! ������������ �������� �������." << endl;
			return false;
		}
		if (strchr(operationsSigns, input[i]) && input[i + 1] == NULL) 
		{
			cout << "������! ���� �������� � ����� ������." << endl;
			return false;
		}
		if (strchr(operationsSigns, input[i]) && input[i + 1] == '-' && input[i + 2] && isalpha(input[i + 2])) //���� ����� ��������� ������� ����� (������� - ������������� �����)
		{	
			arr[(int)input[i+2] - 97] = -1;
			
			i++;	//���������� ����� 
			continue;
		}
		if (input[i] == '(')
		{
			brackets = push(brackets, '('); //����������� ������ ��������� � ����
			continue;
		}
		if (input[i] == ')' && isalpha(input[i + 1]))
		{
			cout << "������� ����� ������." << endl;
			return false;
		}
		if (isalpha(input[i]) && input[i + 1] == '(')
		{
			cout << "������� ����� �������." << endl;
			return false;
		}
		if (input[i] == ')')
		{
			if (brackets != NULL)
			{
				brackets = pop(brackets, t); //��� ������ ������� ����������� ������ - ������� ��������������� ����������� 
				continue;
			}
			else
			{
				cout << "������ � �������." << endl;
				return false;
			}
		}
		if (isalpha(input[i]) && isalpha(input[i + 1]))
		{
			cout << "��� �������� ������." << endl;
			return false;
		}
		if (ispunct(input[i]) && ispunct(input[i + 1]) && input[i + 1] != '(')
		{
			cout << "��� ��������� ������." << endl;
			return false;
		}
		
	}
	if (brackets != NULL) //���� � ����� �������� ���������� ������
	{
		cout << "������ � �������." << endl;
		return false;
	}
}

void convertToPolish(char *input, char *output)
{
	Stack *top = NULL;
	int n = 0; // ��������	
	double inf;
	for (int i = 0; i < strlen(input); i++)
	{
		_strlwr(input); //����������� ������ � ������ �������
		char ch = input[i]; //���������� ������� ������� ������ � ch
		if (ch >= 'a' && ch <= 'z')
		{
			output[n++] = ch;
			continue;
		}
		if (top == NULL || ch == '(')          //����������� ������ ���������� � ����
		{
			top = push(top, ch);
			continue;
		}
		if (ch == ')')            // ����������� �� ����� ��� ����� �������� �� ����������� ������
		{
			while (top->inf != '(')
			{
				top = pop(top, inf);      // ��������� ������� �� �����
				output[n++] = (char)inf;         // ���������� � ������
			}
			top = pop(top, inf);               // ������� �� ����� (
			continue;
		}

		/* ���� ������ � ���� ��������, ������������ �� ����� � ������ output
		��� �������� � ������� ��� ������ ����������� */
		int priority = Prior(ch);
		while (top != NULL && Prior((char)top->inf) >= priority)
		{
			top = pop(top, inf);
			output[n++] = (char)inf;
		}
		top = push(top, ch);
	}
	while (top != NULL)	// ���� ���� �� ����, ������������ ��� �������� � �������� ������
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
			cout << "����� " << (char)(i + 97) << " ����� " ;
			cin >> arr[i];
		}
		if (arr[i] == -1) // ���� ����� ����� ��������� ���
		{
			cout << "����� " << (char)(i + 97) << " ����� ";
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
				cout << "����� - �������������. (������� �� ����)" << endl;
				system("pause");
				exit(1);
			}
			else sp = push(sp, inf1 / inf2); break;
		}
	}
	sp = pop(sp, inf);
	return inf;
}