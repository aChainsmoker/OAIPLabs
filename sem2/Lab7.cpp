#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct flight
{
	string destination;
	string flight_number;
	pair<string, string> departure_time;
};


void AddToTable(flight h[], flight info, int m)
{
	int i = int(info.flight_number[0]) % m;
	if (h[i].flight_number != "")
	{
		int c = 1 + (int(info.flight_number[0]) % (m - 2));
		while (h[i].flight_number != "")
		{
			i = i - c;
			if (i < 0)
				i = i + m;
			c++;
		}
	}
	h[i] = info;
}

flight Search(flight h[], string info, int m)
{
	int i = int(info[0]) % m;
	int c = 1 + (int(info[0]) % (m - 2));
	while (h[i].flight_number != "")
	{
		if (h[i].flight_number == info) 
			return h[i];
		i = i - c;
		if (i < 0)
			i = i + m;
		if (i < 0)
			return { "", "", {0,0} };
		c++;
	}
	return h[i];
}

int main()
{
	setlocale(LC_ALL, "RU");

	int const n = 8, m = 10;
	string key_for_search;

	flight flights[n];
	string destinations[n] = { "Чикаго", "Токио", "Москва", "Минск", "Пекин", "Стамбул", "Копенгаген", "Сеул" };
	string flight_numbers[n] = { "CH-1505", "TK-0183", "MC-0336", "MK-1064", "PK-0984", "ST-7318", "KP-6217", "SL-2108" };
	pair<string, string> departure_time_set[n] = { {"15","10"}, {"07","00"}, {"12","00"}, {"10","15"}, {"04","30"}, {"06","20"}, {"09","50"}, {"00","10"} };

	for (int i = 0; i < 8; i++)
	{
		flights[i].destination = destinations[i];
		flights[i].flight_number = flight_numbers[i];
		flights[i].departure_time = departure_time_set[i];
	}

	flight hash_table[m];

	for (int i = 0; i < n; i++)
		AddToTable(hash_table, flights[i], m);

	cout << "\n\n" << setw(44) << "Исходных массив" << endl; 
	for (int i = 0; i < n; i++)
		cout << setw(20) << flights[i].destination << setw(20) << flights[i].flight_number << setw(20) << flights[i].departure_time.first << ":" << flights[i].departure_time.second << endl;

	cout << "\n\n" << setw(42) << "Хэш таблица" << endl;
	for (int i = 0; i < m; i++)
		if(hash_table[i].flight_number == "")
			cout << setw(20) << "N/A" << setw(18) << "N/A" << setw(24) << "N/A" << endl;
		else
			cout << setw(20) << hash_table[i].destination << setw(20) << hash_table[i].flight_number << setw(20) << hash_table[i].departure_time.first << ":" << hash_table[i].departure_time.second << endl;

	while (key_for_search != "exit")
	{
		cout << endl << "Введите номер рейса для поиска или \"exit\" для выхода из программы: \n";
		cin >> key_for_search;

		flight found_flight = Search(hash_table, key_for_search, m);

		if (found_flight.flight_number == "" && key_for_search != "exit")
			cout << "Рейс не найден";
		else if (found_flight.flight_number != "" && key_for_search != "exit")
			cout << found_flight.destination + " " + found_flight.flight_number + " " << found_flight.departure_time.first << ":" << found_flight.departure_time.second;
	}

	return 0;
}
