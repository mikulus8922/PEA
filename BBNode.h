#pragma once
#include "AdjacencyMatrix.h"
#include "TwoWayList.h"

/// <summary>
/// Struktura wierzcholka wykorzystywanego
/// w algorytmie branch%bound
/// </summary>
struct Node
{
	TwoWayList* roadList;

	AdjacencyMatrix* reducedMatrix;

	//Koszt dotarcia do danego wierzcho;ka
	int cost;
	//Numer wierzcho³ka
	int vertex;
	//zmienna przechowywujaca liczbe sprawdzonych juz wierzcholkow
	int depth;
};