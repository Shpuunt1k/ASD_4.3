#pragma once

#include <string>
#include "List.h"

struct SpSm
{
	void newDot(string name);

	void newEdge(string SS, string TS, float weight);

	void print();

	bool contains(string name);

	double dkstra(string S, string T);

private:

	int stringToInt(string input);

	struct Edge
	{
		int T;
		float weight;

		Edge(int T = NULL, int weight = NULL)
		{
			this->T = T;
			this->weight = weight;
		}
	};

	struct Node
	{
		string name;
		List<Edge*> connections;

		Node(string name = "")
		{
			this->name = name;
		}
	};

	List<Node*> allDots;
};

void SpSm::newDot(string name)
{
	for (int i = 0; i < allDots.GetSize(); ++i)
		if (allDots[i]->name == name)
			throw exception("Attempt to add a new dot with the same name");
	Node* temp = new Node(name);
	allDots.push_back(temp);
}

void SpSm::newEdge(string SS, string TS, float weight)
{
	int S = stringToInt(SS);
	int T = stringToInt(TS);

	if (S > allDots.GetSize() - 1 || T > allDots.GetSize() - 1)
		throw exception("Out of range");
	Edge* temp = new Edge(T, weight);
	allDots[S]->connections.push_back(temp);
}

void SpSm::print()
{
	for (int i = 0; i < allDots.GetSize(); ++i)
	{
		if (allDots[i]->name != "")
			cout << allDots[i]->name;
		else
			cout << i;
		cout << " - ";
		for (int j = 0; j < allDots[i]->connections.GetSize(); ++j)
		{
			if (allDots[allDots[i]->connections[j]->T]->name != "")
				cout << allDots[allDots[i]->connections[j]->T]->name;
			else
				cout << allDots[i]->connections[j]->T;
			cout << " (" << allDots[i]->connections[j]->weight << ")";
			if (j < allDots[i]->connections.GetSize() - 1)
				cout << ", ";
			else
				cout << endl;
		}
		cout << endl;
	}
}

bool SpSm::contains(string name)
{
	for (int i = 0; i < allDots.GetSize(); ++i)
		if (allDots[i]->name == name)
			return true;
	return false;
}

double SpSm::dkstra(string firstS, string secondS)
{
	struct segment
	{
		bool yellow;
		float L;
		int Q;

		segment()
		{
			yellow = false;
			L = -1;
			Q = 9999999999;
		};
	};

	int first = stringToInt(firstS);
	int second = stringToInt(secondS);

	segment* line = new segment[allDots.GetSize()];
	line[first].yellow = true;
	line[first].L = 0;
	bool yellow = true;
	int active = first;
	while (yellow == true)
	{
		yellow = false;
		for (int i = 0; i < allDots[active]->connections.GetSize(); ++i)
		{
			float newP = line[active].L + allDots[active]->connections[i]->weight;
			float oldP = line[allDots[active]->connections[i]->T].L;
			int outOf = line[allDots[active]->connections[i]->T].Q;
			if ((oldP == -1) || (oldP > newP))
			{
				line[allDots[active]->connections[i]->T].L = newP;
				line[allDots[active]->connections[i]->T].Q = active;
			}
		}

		float min = 9999999999;
		for (int i = 0; i < allDots.GetSize(); ++i)
		{
			if ((line[i].L != -1) && (line[i].L < min) && (line[i].yellow == false))
			{
				active = i;
				min = line[i].L;
				yellow = true;
			}
		}
		if (yellow == true)
			line[active].yellow = true;
		else
			throw exception("Couldn't find any path");
		if (line[second].yellow == true)
		{
			string path;
			int reverseSecond = active;
			int reverseFirst = 999999999;
			path.insert(0, allDots[reverseSecond]->name);
			while (reverseFirst != first)
			{
				path.insert(0, " - ");
				reverseFirst = line[reverseSecond].Q;
				path.insert(0, allDots[reverseFirst]->name);
				reverseSecond = reverseFirst;
			}
			path += " ";
			cout << path;
			return line[second].L;
		}
	}
}

int SpSm::stringToInt(string input)
{
	int answer;
	bool success = false;
	for (int i = 0; i < allDots.GetSize(); ++i)
	{
		if (allDots[i]->name == input)
		{
			answer = i;
			success = true;
			break;
		}
	}

	if (success == false)
		throw exception("Couldn't find such dot");
	return answer;
}