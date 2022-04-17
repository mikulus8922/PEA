#include "AdjacencyMatrix.h"
#include <iostream>


AdjacencyMatrix::AdjacencyMatrix()
{
}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& m)
{
	int** tempMatrix = new int* [m.matrixSize];


	for (int i = 0; i < m.matrixSize; i++) {
		tempMatrix[i] = new int[m.matrixSize];
		for (int j = 0; j < m.matrixSize; j++)
			tempMatrix[i][j] = m.adjacencyMatrix[i][j];
	}


	matrixSize = m.matrixSize;
	adjacencyMatrix = tempMatrix;
}

AdjacencyMatrix::AdjacencyMatrix(int size) {
	int** tempMatrix = new int* [size];

	for (int i = 0; i < size; i++) {
		tempMatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
			tempMatrix[i][j] = 0;
	}

	matrixSize = size;
	adjacencyMatrix = tempMatrix;

}


AdjacencyMatrix::~AdjacencyMatrix() {
	if (adjacencyMatrix != nullptr) {
		for (int i = 0; i < matrixSize; i++) {
			delete[] adjacencyMatrix[i];
		}

		delete[] adjacencyMatrix;
		matrixSize = 0;
		adjacencyMatrix = nullptr;
	}
}


void AdjacencyMatrix::addLink(int start, int end, int value)
{
	adjacencyMatrix[start][end] = value;
}


void AdjacencyMatrix::displayMatrixForm()
{
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			std::cout << adjacencyMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "rozmiar: " << matrixSize << std::endl;
}

void AdjacencyMatrix::displayStartEndForm()
{
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			std::cout << i << "," << j << ": " << adjacencyMatrix[i][j] << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "rozmiar: " << matrixSize << std::endl;
}



