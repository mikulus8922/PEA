#pragma once
#include <set>
#include <vector>
#include "AdjacencyMatrix.h"

using std::vector;
using std::set;

/// <summary>
/// Klasa zawierajaca funkcje wykorzystywane przy obliczaniu
/// algorytmu branch and bound
/// </summary>
class HeldKarp
{
public:
	int* smallestRoadArray;
	int matrixSize;
	int minCost = INT_MAX;
private:
	/// <summary>
	/// Funkcja pomocnicza generujaca wszystkie podzbiory wierzcholkow
	/// zadanego grafu i zapisujaca je w zmiennej allSets
	/// </summary>
	/// <param name="index"></param>
	/// <param name="numberOfVertices"></param>
	/// <param name="vertices"></param>
	/// <param name="allSets"></param>
	/// <param name="currentSet"></param>
	void calculateAllSets(int index, int numberOfVertices, int* vertices, vector<set<int>>* allSets, set<int>currentSet);
public:
	/// <summary>
	/// Glowna funkcja obliczajaca minimalny cykl dla danego grafu
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	int calculateHeldKarp(AdjacencyMatrix* matrix);

};
