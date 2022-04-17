#pragma once
#include "AdjacencyMatrix.h"

/// <summary>
/// Klasa zawierajaca funkcje wykorzystywane przy obliczaniu
/// algorytmu Symulowanego Wyzarzania
/// </summary>
class SimulatedAnnealing
{
public:

	int smallestCost;
	int currentCost;
	int bestCost;

	int roadSize;
	int* smallestRoadArray;
	int* currnetRoadArray;
	int* bestRoadArray;

	/// <summary>
	/// Funkcja pomocnicza obliczajaca poczatkowa temperature
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	double calculateStartingTemperature(AdjacencyMatrix* matrix);

	/// <summary>
	/// Funkcja zamieniajace 2 losowe wierzcholki w cylku
	/// </summary>
	void randomChange();

	/// <summary>
	/// Funcka obliczajaca prawdopodobienstwo temperaturowe
	/// </summary>
	/// <param name="temperatureCurrent"></param>
	/// <returns></returns>
	double calculateProbability(double temperatureCurrent);

	/// <summary>
	/// Funkcja pomocnicza obliczaj¹ca koszt zadanego cyklu
	/// </summary>
	/// <param name="matrix"></param>
	/// <param name="road"></param>
	/// <returns></returns>
	int calculateCost(AdjacencyMatrix* matrix, int* road);

	/// <summary>
	/// Glowna funkcja obliczajaca minimalny cykl dla danego grafu
	/// </summary>
	/// <param name="matrix"></param>
	/// <param name="maxTime"></param>
	/// <param name="temperatureCooling"></param>
	/// <param name="epoch"></param>
	/// <returns></returns>
	int calculateSimulatedAnnealing(AdjacencyMatrix* matrix,
		double maxTime, double temperatureCooling, int epoch);
};

