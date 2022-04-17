#pragma once
#include "TabuList.h"
#include "AdjacencyMatrix.h"

/// <summary>
/// Klasa zawierajaca funkcje wykorzystywane przy obliczaniu
/// algorytmu Tabu Search
/// </summary>
class Tabu
{
private:
	/// <summary>
	/// Funkcja pomocnicza zwracajaca najlepszego kandydata na nowy cykl
	/// </summary>
	/// <param name="road"></param>
	/// <returns></returns>
	int* getBestCandidate(int* road);
	int* currentRoad;
	TabuList* tabuList;
	AdjacencyMatrix* matrix;

	/// <summary>
	/// Funkcja pomocnicza zamieniajaca miedzy sob¹ 2 losowe wierzcholki grafu
	/// </summary>
	void randomSwap();

	/// <summary>
	/// Funkcja pomocnicza zamieniajaca miedzy sob¹ 2 wskazane wierzcholki grafu
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	void swap(int* a, int* b);
	int bestChange[2];

	/// <summary>
	/// Funkcja pomocnicza obliczaj¹ca koszt zadanego cyklu
	/// </summary>
	/// <param name="road"></param>
	/// <returns></returns>
	int calculateRoad(int* road);
public:

	int matrixSize;
	int* bestRoad;
	/// <summary>
	/// Glowna funkcja obliczajaca minimalny cykl dla danego grafu
	/// </summary>
	/// <param name="m"></param>
	/// <param name="maxTime"></param>
	/// <param name="maxTabuSize"></param>
	/// <returns></returns>
	int calculateTabu(AdjacencyMatrix* m, double maxTime, int maxTabuSize);
};
