#pragma once
#include "AdjacencyMatrix.h"
#include <string>
#include <fstream>

using std::string;

/// <summary>
/// Klasa zawierajaca funkcje umozliwiajace ladowanie grafu
/// z pliku tekstowego
/// </summary>
class LoadGraphFromFile
{
private:
	std::ifstream fileStream;
	string filePath;

public:
	LoadGraphFromFile();
	~LoadGraphFromFile();

	/// <summary>
	/// Funkcja umozliwiajaca wybranie pliku
	/// </summary>
	/// <returns></returns>
	bool chooseFile();

	/// <summary>
	/// Funkcja sczytujaca dane z pliku do macierzy
	/// </summary>
	/// <returns></returns>
	AdjacencyMatrix* loadFromFile();

};

