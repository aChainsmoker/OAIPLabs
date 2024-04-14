#include <iostream>

using namespace std;

struct Spisok
{
	int info;
	Spisok* next, * prev;
} *beginSpis, * endSpis, *beginSpis2, *endSpis2;


void Add(Spisok** b, Spisok** e, int in, int way) {
	Spisok* t = new Spisok;
	t->info = in;
	t->next = t->prev = NULL;
	if (*b != NULL)
	{
		if(way == 1)
		{ 
			t->prev = NULL;
			t->next = *b; 
			(*b)->prev = t; 
			*b = t;
		}
		else
		{
			t->next = NULL; 
			t->prev = *e; 
			(*e)->next = t; 
			*e = t;
		}
	}
		
	else 
	{
		*b = *e = t;
	}
}


int OutStack(Spisok** b, Spisok** e, int way)
{
	Spisok* t;
	int out;
	if (way == 1)
	{
		t = *b;
		out = (*b)->info;
		*b = (*b)->next;
		(*b)->prev = NULL;
		
	}
	else
	{
		t = *e;
		out = (*e)->info;
		*e = (*e)->prev;
		(*e)->next = NULL;
	}
	delete t;
	return out;
}

void View(Spisok* b, Spisok* e, int way)
{
	if (way == 1)
	{
		Spisok* t = b;
		while (t != NULL)
		{
			cout << t->info << " ";
			t = t->next;
		}
	}
	else
	{
		Spisok* t = e;
		while (t != NULL)
		{
			cout << t->info << " ";
			t = t->prev;
		}
	}
	cout << endl;
}


void Delete_All(Spisok** p)
{
	while (*p != NULL)
	{
		Spisok* t = *p;
		*p = (*p)->next;	
		delete t;
	}
}


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

void Sort_adress(Spisok** b, Spisok** e)
{
	Add(b, e, 0, 1);
	Spisok* t = NULL, * t1, * r;
	if ((*b)->next->next == NULL) return;
	do
	{
		for (t1 = *b; t1->next->next != t; t1 = t1->next)
			if (t1->next->info > t1->next->next->info)
			{
				r = t1->next->next;
				if(r->next!=NULL)
					r->next->prev = t1->next;
				t1->next->next = r->next;
				t1->next->prev = r;
				r->next = t1->next;
				r->prev = t1;
				t1->next = r;
			}
		if (t == NULL)
			*e = t1->next;
		t = t1->next;
	} while ((*b)->next->next != t);

	OutStack(b, e, 1);
}

void Sort_info(Spisok* p)
{
	Spisok* t = NULL, * t1;
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




void CopyCertainElementsToTheAnotherStack(Spisok** b, Spisok** e , Spisok** b1, Spisok** e1, int way)
{
	if (way == 1)
	{
		Spisok* t = *b;
		Spisok* max_ = t;
		while (t->next != NULL)
		{
			if (t->next->info > max_->info)
				max_ = t->next;
			t = t->next;
		}

		t = *b;

		while (t != max_)
		{
			Spisok* k = NULL;
			if (t != *b)
			{
				Add(b1, e1, t->info, 1);
				k = t;
				(*b)->next = (*b)->next->next;
				(*b)->next->prev = (*b);
			}

			t = t->next;
			delete k;
		}
	}
	else
	{
		Spisok* t = *e;
		Spisok* max_ = t;
		while (t->prev != NULL)
		{
			if (t->prev->info > max_->info)
				max_ = t->prev;
			t = t->prev;
		}

		t = *e;

		while (t != max_)
		{
			Spisok* k = NULL;
			if (t != *e)
			{
				Add(b1, e1, t->info, 2);
				k = t;
				(*e)->prev = (*e)->prev->prev;
				(*e)->prev->next = (*e);
			}

			t = t->prev;
			delete k;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RU");

	int kod, way, n;
	while (true)
	{
		cout << "\n1 - Создать список \n2 - Добавить элемент в список \n3 - Просмотреть список \n4 - Достать элемент из списка \n5 - Очистить списки \n6 - Сортировать список обменом адресов \n7 - Сортировать список обменом информации \n8 - Перенести элементы списка между его веришной и элементом с максимальным значением в новый список \n9 - Просмотреть второй список \n0 - Выход \n";
		cin >> kod;
		switch (kod)
		{

		case 1: 
			if (beginSpis != NULL)
				cout << "Список уже создан\n";
			else {
				cout << "Введите количество добавляемых элемнтов: ";
				cin >> n;
				for (int i = 0; i < n; i++)
				{
					int in = Random(i);
					Add(&beginSpis, &endSpis, in, 1);
				}
			}
			break;
		case 2:
			cout << "Добавить элементы в: \n1 - Начало \n2 - Конец \n";
			cin >> way;
			cout << "Введите количество добавляемых элемнтов: ";
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				int in = Random(i);
				Add(&beginSpis, &endSpis, in, way);
			}
			break;
		case 3:
			if (beginSpis != NULL)
			{
				cout << "Просмотреть элементы \n1 - С начала \n2 - В обратном порядке \n";
				cin >> way;
				cout << "---List--- \n";
				View(beginSpis, endSpis, way);
			}
			else
				cout << "Список пуст\n";
			break;
		case 4:
			if (beginSpis != NULL)
			{
				cout << "Взять элементы из: \n1 - Начала \n2 - Конца \n";
				cin >> way;
				cout << "Был взят элемент: " << OutStack(&beginSpis, &endSpis, way) << endl;;
			}
			else
				cout << "Список пуст\n";
			break;
		case 5:
			Delete_All(&beginSpis);
			Delete_All(&beginSpis2);
			cout << "Списки удалены!" << endl;
			break;
		case 6:
			if (beginSpis != NULL)
			{
				Sort_adress(&beginSpis, &endSpis);
			}
			else
				cout << "Список пуст\n";
			break;
		case 7:
			if (beginSpis != NULL)
			{
				Sort_info(beginSpis);
			}
			else
				cout << "Список пуст\n";
			break;
		case 8:
			if (beginSpis != NULL)
			{
				cout << "Перемещение элементов \n1 - Между началом списка и элементом с максимальным значением \n2 - Между концом списка и элементом с максимальным значением \n";
				cin >> way;
				CopyCertainElementsToTheAnotherStack(&beginSpis, &endSpis, &beginSpis2, &endSpis2, way);
				if (beginSpis2 == NULL)
					cout << "Элементы не были перенесены, т.к. в заданном диапазоне нет элементов удовлетворяющих условию" << endl;
			}
			else
				cout << "Изначальный список пуст\n";
			break;
		case 9:
			if (beginSpis2 != NULL)
			{
				cout << "Просмотреть элементы \n1 - С начала \n2 - В обратном порядке \n";
				cin >> way;
				cout << "---Second_List--- \n";
				View(beginSpis2, endSpis2, way);
			}
			else
				cout << "Список пуст\n";
			break;
		case 0:
			if (beginSpis != NULL)
			{
				Delete_All(&beginSpis);
			}
			if (beginSpis2 != NULL)
			{
				Delete_All(&beginSpis2);
			}
			return 0;
		}
	}

}