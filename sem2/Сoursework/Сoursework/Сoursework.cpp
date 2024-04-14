#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <math.h>
#include <iomanip>

using namespace std;

struct Employee
{
    string name;
    string surname;
    string patronymic;
    string personnel_number;
    int work_hours;
    double hourly_rate;
    double salary;
};

int amount_of_workers = 0;
Employee* staff;
Employee* staffInInitialOrder = NULL;

#pragma region Декларация методов
double CountSalary(int, double);
void BubbleSorting();
void QuickSort(int, int);
void HeapSort(int);
void LinearSearch();
void BinarySearch();
#pragma endregion

#pragma region Чтение и Запись
void ReadEmployees()
{
    ifstream file;
    string useless_str;
    file.open("Employees.txt");
    file >> amount_of_workers;
    staff = new Employee[amount_of_workers];
    for (int i=0;i < amount_of_workers; i++ )
    {
        file >> useless_str;
        file >> staff[i].name;
        file >> useless_str;
        file >> staff[i].surname;
        file >> useless_str;
        file >> staff[i].patronymic;
        file >> useless_str;
        file >> useless_str;
        file >> staff[i].personnel_number;
        file >> useless_str;;
        file >> useless_str;;
        file >> staff[i].work_hours;
        file >> useless_str;
        file >> useless_str;;
        file >> staff[i].hourly_rate;
        file >> useless_str;
        staff[i].salary = CountSalary(staff[i].work_hours, staff[i].hourly_rate);
    }


    file.close();
}

void WriteEmployees(string file_name, Employee* staff, int amount_of_workers)
{
    ofstream file;
    file.open(file_name);
    file << amount_of_workers << endl;
    for (int i = 0; i < amount_of_workers; i++)
    {
        file << "Имя: " << staff[i].name << endl;
        file << "Фамилия: " << staff[i].surname << endl;
        file << "Отчество: " << staff[i].patronymic << endl;
        file << "Табельный номер: " << staff[i].personnel_number << endl;
        file << "Рабочие часы: " << staff[i].work_hours << endl;
        file << "Почасовая ставка: " << staff[i].hourly_rate << endl;
        file << "--------------------------------------------------------------- \n";
    }
    file.close();
}
#pragma endregion




double CountSalary(int hours, double rate)
{
    int time_bar = 144;
    
    double salary;

    if (hours > time_bar)
    {
        int overtime = hours - time_bar;
        salary = (2 * rate) * overtime + time_bar * rate;
    }
    else
    {
        salary = hours * rate;
    }
    return salary*0.88;
}

void AddEmployee()
{
    Employee person;

    cout << endl << "Введите имя Сотрудника\n";
    cin >> person.name;

    cout << endl << "Введите фамилию Сотрудника\n";
    cin >> person.surname;

    cout << endl << "Введите отчество Сотрудника\n";
    cin >> person.patronymic;

    cout << endl << "Введите табельный номер Сотрудника\n";
    cin >> person.personnel_number;

    cout << endl << "Введите количество часов, которые сотрудник отработал за текущий месяц\n";
    cin >> person.work_hours;

    cout << endl << "Введите почасовую ставку Сотрудника\n";
    cin >> person.hourly_rate;

    person.salary = CountSalary(person.work_hours, person.hourly_rate);

    amount_of_workers++;

    Employee* newStaff= new Employee[amount_of_workers];

    for (int i = 0; i < amount_of_workers-1; i++)
    {
        newStaff[i] = staff[i];
    }

    newStaff[amount_of_workers - 1] = person;

    delete[] staff;

    staff = newStaff;
}

void AddEmployee(Employee** foundStaff, int number_of_matches, Employee person)
{
    Employee* newStaff = new Employee[number_of_matches];
    for (int i = 0; i < number_of_matches - 1; i++)
    {
         newStaff[i] = *foundStaff[i];
    }

    newStaff[number_of_matches - 1] = person;
    
    
    delete[] *foundStaff;

    *foundStaff = newStaff;
}


void FindEmployees()
{
    int action;
    cout << "Выберите метод поиска Сотрудников:\n1 - Линейный\n2 - Бинарный\n";
    cin >> action;
    switch (action)
    {
    case 1:
        LinearSearch();
        break;
    case 2:
        BinarySearch();
        break;
    }
}

void ShowEmployees(Employee* staff, int amount_of_workers, bool foundEmployees)
{
    string file_name = "Employees.txt";

    int action;
    
    cout << endl<< "Выберите способ вывода Сотрудников:\n1 - В порядке их добавления в список\n2 - Отсортированном виде (Метод пузырька)\n3 - В отсортированном виде (QuickSort)\n4 - В отсортированном виде (HeapSort)\n";
    
    if (!foundEmployees)
        cin >> action;
    else
        action = 5;

    switch (action)
    {
    case 1:
        break;
    case 2:
        BubbleSorting();
        file_name = "Sorted_Employees.txt";
        break;
    case 3:
        QuickSort(0, amount_of_workers-1);
        file_name = "Sorted_Employees.txt";
        break;
    case 4:
        HeapSort(amount_of_workers);
        file_name = "Sorted_Employees.txt";
        break;
    case 5: 
        file_name = "FoundEmployees.txt";
        break;
    }
    
    cout << setw(20) << "Имя" << '|' << setw(20) << "Фамилия" << '|' << setw(20) << "Отчество" << '|' << setw(20) << "Табельный номер" << '|' << setw(20) << "Отработанные часы" << '|' << setw(20) << "Почасовая ставка" << '|' << setw(20) << "Заработная плата" << '|' << endl;
    for (int i = 0; i < amount_of_workers; i++)
    {
        cout << setw(20) << staff[i].name << '|' << setw(20) << staff[i].surname << '|' << setw(20) << staff[i].patronymic << '|' << setw(20) << staff[i].personnel_number << '|' << setw(20) << staff[i].work_hours << '|' << setw(20) << staff[i].hourly_rate << '|' << setw(20) << staff[i].salary << '|' << endl;
    }

    WriteEmployees(file_name, staff, amount_of_workers);
}


#pragma region Сохранение считанного из файла порядка сотрудников
void TakeCopyOfStaff()
{
    if (staffInInitialOrder != NULL)
        delete[] staffInInitialOrder;
    staffInInitialOrder = new Employee[amount_of_workers];
    for (int i = 0; i < amount_of_workers; i++)
    {
        staffInInitialOrder[i] = staff[i];
    }
}
void ResetStaffOrder()
{
    for (int i = 0; i < amount_of_workers; i++)
    {
        staff[i] = staffInInitialOrder[i];
    }
}
#pragma endregion

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int action;

    ReadEmployees();

    TakeCopyOfStaff();

    while (true)
    {
        cout << "\nВведите номер действия:\n1 - Добавить Работника\n2 - Вывести список сотрудников\n3 - Найти Работника по заработной плате\n0 - Завершить программу\n";
        cin >> action;
        switch (action)
        {
        case 1:
            AddEmployee();
            TakeCopyOfStaff();
            break;
        case 2:
            ShowEmployees(staff, amount_of_workers, false);
            ResetStaffOrder();
            break;
        case 3:
            FindEmployees();
            ResetStaffOrder();
            break;

        default:
            WriteEmployees("Employees.txt", staff, amount_of_workers);
            delete[] staffInInitialOrder;
            delete[] staff;
            return 0;
        }

    }
}


#pragma region Методы сортировки
void BubbleSorting()
{
    for (int i = 0; i < amount_of_workers - 1; i++)
    {
        for (int j = i + 1; j < amount_of_workers; j++)
        {
            if (staff[i].salary > staff[j].salary)
            {
                Employee r;
                r = staff[i];
                staff[i] = staff[j];
                staff[j] = r;
            }
        }
    }
}


int partition(int start, int end)
{
    Employee pivot = staff[end]; // Опорный элемент (pivot)
    int i = start - 1; // Индекс меньшего элемента

    for (int j = start; j < end; ++j)
    {
        // Если текущий элемент меньше или равен опорному элементу
        if (staff[j].salary <= pivot.salary)
        {
            // Увеличиваем индекс меньшего элемента и меняем местами элементы
            ++i;
            swap(staff[i], staff[j]);
        }
    }
    // Помещаем опорный элемент в правильное положение в массиве и возвращаем его индекс
    swap(staff[i + 1], staff[end]);
    return i + 1;
}

void QuickSort(int start, int end)
{
    if (start < end)
    {
        // Индекс опорного элемента (pivot) после разделения
        int pi = partition(start, end);

        // Рекурсивно сортируем элементы до и после опорного элемента
        QuickSort(start, pi - 1); \
            QuickSort(pi + 1, end);
    }
}




void heapify(int n, int i)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && staff[l].salary > staff[largest].salary)
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && staff[r].salary > staff[largest].salary)
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(staff[i], staff[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(n, largest);
    }
}


void HeapSort(int n)
{
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(staff[0], staff[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(i, 0);
    }
}

#pragma endregion


#pragma region Алгоритмы поиска
void LinearSearch()
{
    int number_of_matches = 0;
    double key;
    cin >> key;

    Employee* foundEmployees = new Employee[0];
    for (int i = 0; i < amount_of_workers; i++)
    {
        if (round(staff[i].salary * 10000)/10000 == round(key*10000)/10000)
        {
            number_of_matches++;
            AddEmployee(&foundEmployees, number_of_matches, staff[i]);
        }
    }
    ShowEmployees(foundEmployees, number_of_matches, true);
}


void BinarySearch()
{

    double key;
    cin >> key;

    QuickSort(0, amount_of_workers - 1);

    int left = 0;
    int right = amount_of_workers - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (round(staff[mid].salary * 10000) / 10000 == round(key * 10000) / 10000)
        {
            Employee foundEmployee = staff[mid];
            ShowEmployees(&foundEmployee, 1, true);
            return;
        }
        else if (staff[mid].salary > key)
            right = mid - 1;
        else if (staff[mid].salary < key)
            left = mid + 1;
    }

}
#pragma endregion