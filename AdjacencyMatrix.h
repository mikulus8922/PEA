#pragma once

/// <summary>
/// Klasa przechowywujaca tablice dwuwymiarowa opisujaca graf
/// oraz funkcje pomocnicze
/// </summary>
class AdjacencyMatrix
{
public:
	int matrixSize;
	int** adjacencyMatrix;

	AdjacencyMatrix();
	AdjacencyMatrix(const AdjacencyMatrix& m);
	AdjacencyMatrix(int size);

	~AdjacencyMatrix();

	void addLink(int start, int end, int value);
	//Wyswietla tablice w formie tablicy dwuwymiarowej
	void displayMatrixForm();
	//Wyswietla tablice w formie w. startowy, w. koncowy: koszt drogi
	void displayStartEndForm();
};

