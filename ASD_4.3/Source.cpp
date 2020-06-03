#include <iostream>
#include <fstream>

#include "SpSm.h"

using namespace std;

int main()
{
	ifstream file;
	file.open("input.txt");
	file.unsetf(ios::skipws);
	string tempS;
	char tempC;
	SpSm timetable;
	while (!file.eof())
	{
		file >> tempC;
		while (tempC != ';')
		{
			tempS += tempC;
			file >> tempC;
		}
		string arrival = tempS;
		if (timetable.contains(arrival) == false)
			timetable.newDot(arrival);
		tempS.clear();

		file >> tempC;
		while (tempC != ';')
		{
			tempS += tempC;
			file >> tempC;
		}
		string T = tempS;
		if (timetable.contains(T) == false)
			timetable.newDot(T);
		tempS.clear();

		file >> tempC;
		while (tempC != ';')
		{
			tempS += tempC;
			file >> tempC;
		}
		if (tempS != "N/A")
		{
			float price = stoi(tempS);
			timetable.newEdge(arrival, T, price);
		}
		tempS.clear();

		file >> tempC;
		while (tempC != '\n' && !file.eof())
		{
			tempS += tempC;
			file >> tempC;
		}
		if (tempS != "N/A")
		{
			float price = stoi(tempS);
			timetable.newEdge(T, arrival, price);
		}
		tempS.clear();
	}
	timetable.print();
	cout << timetable.dkstra("City1", "City8");
}