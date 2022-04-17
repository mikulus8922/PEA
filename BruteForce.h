#pragma once
#include "AdjacencyMatrix.h"

/// <summary>
/// Klasa zawierajaca funkcje wykorzystywane przy obliczaniu
/// algorytmu brute force
/// </summary>
class BruteForce
{
public:
	int* indexArray;
	int matrixSize;
	int smallestRoad;
	int* smallestRoadArray;
private:
	AdjacencyMatrix* matrix;

	/// <summary>
	/// Funckja pomocnicza zamieniajaca 2 wartosci w podanych adresach
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	void swap(int* a, int* b);

	/// <summary>
	/// Funkcja pomocnicza zwracajaca najkrotszy cykl z wszystkih permutacji
	/// </summary>
	/// <returns></returns>
	int calculateRoad();

	/// <summary>
	/// Rekurencyjna funkcja pomocnicza wypisujaca wszystkie permutacje
	/// </summary>
	/// <param name="depth"></param>
	/// <returns></returns>
	int nextPermutation(int depth);
public:
	/// <summary>
	/// Glowna funkcja zwracajaca minimalny cykl w grafie
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	int calculateBruteForce(AdjacencyMatrix* matrix);

};

