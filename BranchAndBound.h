#pragma once
#include "AdjacencyMatrix.h"
#include <limits>
#include "BBNode.h"
#include "TwoWayList.h"

/// <summary>
/// Klasa zawierajaca funkcje wykorzystywane przy obliczaniu
/// algorytmu branch and bound
/// </summary>
class BranchAndBound
{
public:
	//Lista przechowywujaca najktorszy cykl
	TwoWayList* smallestRoadList;
private:
	//Zmienna przechowywujaca najnizszy koszt przed wyczyszczeniem kolejki
	int lowestCost = INT_MAX;
	
	/// <summary>
	/// Funkcja pomocnicza ustawiajaca INT_MAX na przekatnej macierzy
	/// </summary>
	/// <param name="matrix"></param>
	void clearDiagonal(AdjacencyMatrix* matrix);

	/// <summary>
	/// Funkcja pomocnicza tworzaca nowy wierzcho³ek i redukuj¹ca 
	/// macierz dla tego wierzcho³ka
	/// </summary>
	/// <param name="parentMatrix"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="depth"></param>
	/// <param name="roadList"></param>
	/// <returns></returns>
	Node* createNewNode(AdjacencyMatrix* parentMatrix, int from, int to, int depth, TwoWayList roadList);
	
	/// <summary>
	/// Funkcja pomocnicza obliczajaca koszt dotarcia do wierzcholka to z wierzcholka from
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	int calculateNodeCost(AdjacencyMatrix* matrix);
public:
	/// <summary>
	/// Glowna funkcja obliczajaca minimalny cykl dla danego grafu
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	int calculateBranchAndBound(AdjacencyMatrix* matrix);

};

