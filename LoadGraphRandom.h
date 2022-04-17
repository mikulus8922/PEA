#pragma once
#include "AdjacencyMatrix.h"

/// <summary>
/// Klasa zawierajaca funkcje umozliwiajaca 
/// generowanie grafow z losowymi danymi
/// </summary>
class LoadGraphRandom
{
public:
	LoadGraphRandom();

	/// <summary>
	/// Funkcja generujaca losowy graf o zadanym rozmiarze
	/// </summary>
	/// <param name="size"></param>
	/// <returns></returns>
	AdjacencyMatrix* generateRandomGraph(int size);

};

