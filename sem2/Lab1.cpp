#include <iostream>

using namespace std;

double x, a;

//Обычная функция
double usualFunc(double x0)
{

    while (x != x0)
    {
        x0 = x;
        x = 0.5 * (x + a / x);
        
    }

    return x;

}

//Рекурсивная функция
double recursionFunc(double x0)
{

    x = 0.5 * (x + a / x);

    if (x0 != x)
    {
        x0 = x;
        recursionFunc(x0);
    }
    

    return x;
}

int main()
{

    setlocale(LC_ALL, "Russian");

    cout << "Введите a: ";

    cin >> a;

    //Записываем начальное значение X
    x = 0.5 * (1 + a);

    cout << "Результат обычной функции = " << usualFunc(-1) << endl;;

    //Записываем начальное значение X
    x = 0.5 * (1 + a);

    cout << "Результат рекурсивной функции = " << recursionFunc(-1) << endl;
}

