#include <iostream>
#include<string>
#include <set>
#include <vector>

using namespace std;

set <char> znak;
double results[200];
vector<char> letters;

struct Stack {
	char info;
	double infoD;
	Stack* next;
}*Vertex;


void InStack(Stack** p, char in)
{
	Stack* t = new Stack;
	t->info = in;
	t->next = *p;
	*p = t;
}

char OutStack(Stack** p)
{
	Stack* t = *p;
	char out;
	out = (*p)->info;
	*p = (*p)->next;
	delete t;
	return out;
}


int PrioSet(char symbol)
{
	switch (symbol)
	{
	case '^': return 4;
	case '*': case '/': return 3;
	case '-': case '+': return 2;
	case '(': return 1;
	}
	return 0;
}

void Del_All(Stack** p)
{
	while (*p != NULL)
	{
		Stack* t = *p;
		*p = (*p)->next;
		delete t;
	}
}


string EnterData()
{
	string str;
	cout << "Введите выражение: " << endl;
	cin >> str;

	return str;
}


string Reform(string str)
{
	string outStr;
	for (int k = 0; k < str.size(); k++)
	{
	
		if (str[k] == '(')
			InStack(&Vertex, str[k]);
		if (str[k] == ')')
		{
	
			while ((Vertex->info) != '(')
			{
				outStr += OutStack(&Vertex);
			}
			OutStack(&Vertex);
		}


		if (str[k] >= 'a' && str[k] <= 'z')
		{
			outStr += str[k];
			letters.push_back(str[k]);
		}

		
		if (znak.count(str[k]) == 1)
		{
			while (Vertex != NULL && PrioSet(Vertex->info) >= PrioSet(str[k]))
			{
				outStr += OutStack(&Vertex);;
			}
			InStack(&Vertex, str[k]);
		}
	}

	while (Vertex != NULL)
	{
		outStr += OutStack(&Vertex);;
	}

	return outStr;
}



void EnterValues(string str)
{
	int amount_of_letters = 0;
	vector<double> values;

	cout << endl << "Введите значения: " << endl;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			double val;
			cout << endl << str[i] << "= ";
			cin >> val;
			values.push_back(val);
			amount_of_letters++;

		}
	}

	for (int i = 0; i < amount_of_letters; i++)
	{
		results[int(letters[i])] = values[i];
	}
}


double Rezult(string str)
{
	char var1, var2;
	double op1, op2, rez;
	char rezVar = 'z' + 1;
	for (int i = 0; i < str.size(); i++)
	{
		if (!znak.count(str[i]))
			InStack(&Vertex, str[i]);
		else
		{
			var1 = OutStack(&Vertex);
			var2 = OutStack(&Vertex);
			op1 = results[int(var1)];
			op2 = results[int(var2)];
			switch (str[i])
			{
			case '+': rez = op2 + op1; break;
			case '-': rez = op2 - op1; break;
			case '*': rez = op2 * op1; break;
			case '/': rez = op2 / op1; break;
			case '^': rez = pow(op2, op1); break;
			}
			results[int(rezVar)] = rez;
			InStack(&Vertex, rezVar);
			rezVar++;
		}
	}
	return rez;
}


int main()
{
	setlocale(LC_ALL, "RU");

	Vertex = NULL;
	string str;
	str = EnterData();

	znak.insert('*');
	znak.insert('/');
	znak.insert('+');
	znak.insert('-');
	znak.insert('^');

	cout << endl << "Обратная польская запись: " << Reform(str) << endl;
	EnterValues(Reform(str));
	cout << endl << "Результат: " << Rezult(Reform(str));

	Del_All(&Vertex);
	return 0;
}