#include <iostream>

using namespace std;

struct Stack
{
	int info;
	Stack* next;
} *Vertex, * Second_Vertex;


int Random(int num)
{
	int multiplier;

	srand(time(nullptr) + num);

	if (rand() % 2 == 0)
		multiplier = 1;
	else
		multiplier = -1;

	return (rand() % 100) * multiplier;
}

void InStack(Stack** p, int in)
{
	Stack* t = new Stack;
	t->info = in;
	t->next = *p;
	*p = t;
}

void View(Stack* p)
{
	Stack* t = p;
	while (t != NULL)
	{
		cout << t->info << " ";
		t = t->next;
	}
	cout << endl;
}

void CopyCertainElementsToTheAnotherStack(Stack** p, Stack** b)
{
	Stack* t = *p;
	Stack* max_ = t;
	while (t->next != NULL)
	{
		if (t->next->info > max_->info)
			max_ = t->next;
		t = t->next;
	}

	t = *p;

	while (t != max_)
	{
		Stack* k = NULL;
		if (t != *p)
		{
			InStack(b, t->info);
			k = t;
			(*p)->next = (*p)->next->next;
		}

		t = t->next;
		delete k;
	}

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
int OutStack(Stack** p)
{
	Stack* t = *p;
	int out;
	out = (*p)->info;
	*p = (*p)->next;
	delete t;
	return out;
}


void Sort_adress(Stack** p)
{
	InStack(p, 0);
	Stack* t = NULL, * t1, * r;
	if ((*p)->next->next == NULL) return;
	do {
		for (t1 = *p; t1->next->next != t; t1 = t1->next)
			if (t1->next->info > t1->next->next->info) {
				r = t1->next->next;
				t1->next->next = r->next;
				r->next = t1->next;
				t1->next = r;
			}
		t = t1->next;
	} while ((*p)->next->next != t);
	
	OutStack(p);
}


void Sort_info(Stack* p)
{
	Stack* t = NULL, * t1;
	int r;
	do {
		for (t1 = p; t1->next != t; t1 = t1->next)
		{
			if (t1->info > t1->next->info) {
				r = t1->info;
				t1->info = t1->next->info;
				t1->next->info = r;
			}
		}	
		t = t1;
	} while (p->next != t);
}


int main()
{
	setlocale(LC_ALL, "RU");


	int i, in, n, kod;
	while (true) 
	{
		cout << "\nСоздать стэк - 1.\nДобавить элементы в стек - 2.\nПросмотреть стэк - 3.\nДостать элемент стэка - 4. \nУдалить стэки - 5. \nСортировать стэк обменом адресов - 6. \nСортировать стэк обменом информации  - 7. \nПеренести элементы стэка между его вершиной и элементом с наибольшим значением в другой стэк - 8. \nПросмотреть второй стэк - 9 \nВыход - 0.\n";
		cin >> kod;
		switch (kod)
		{
		case 1: case 2:
			if (kod == 1 && Vertex != NULL)
			{
				cout << "Очистите память сначала" << endl;
				break;
			}
			cout << "Введите количество элементов: ";
			cin >> n;
			cout << endl;

			for (i = 1; i <= n; i++)
			{
				in = Random(i);
				InStack(&Vertex, in);
			}

			break;

		case 3:
			if (!Vertex)
			{
				cout << "Стэк пуст!" << endl;
				break;
			}
			cout << "--- Stack ---" << endl;
			View(Vertex);
			break;
		case 4:
			if (Vertex != NULL)
			{
				int a = OutStack(&Vertex);
				cout << "Из стэка был взят элемент: " << a << endl;
			}
			else
			{
				cout << "Стэк пуст!" << endl;
			}

			break;
		case 5:
			Del_All(&Vertex);
			Del_All(&Second_Vertex);
			cout << "Память очищена!" << endl;
			break;
		case 6:
			if(Vertex != NULL)
				Sort_adress(&Vertex);
			else
				cout << "Стэк пуст!" << endl;
			break;

		case 7:
			if (Vertex != NULL)
				Sort_info(Vertex);
			else
				cout << "Стэк пуст!" << endl;
			break;
		case 8:
			if (Second_Vertex != NULL)
				cout << "Элементы уже были скопированы, так что, чтобы повторить операцию, сначала очистите память" << endl;
			else
			{
				if (Vertex == NULL)
				{
					cout << "Изначальный стэк пуст!" << endl;
					break;
				}
				CopyCertainElementsToTheAnotherStack(&Vertex, &Second_Vertex);
				if (Second_Vertex == NULL)
					cout << "Элементы не были перенесены, т.к. нет элементов удовлетворяющих условию" << endl;
			}
			break;
		case 9:
			if (!Second_Vertex)
			{
				cout << "Стэк пуст!" << endl;
				break;
			}
			cout << "---Second_Stack---" << endl;
			View(Second_Vertex);
			break;
		case 0:
			if (Vertex != NULL)
				Del_All(&Vertex);
			if (Second_Vertex != NULL)
				Del_All(&Second_Vertex);
			return 0; 
		}
	}
}