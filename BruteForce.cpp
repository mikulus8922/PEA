#include "BruteForce.h"
#include <iostream>
#include <limits>

void BruteForce::swap(int* a, int* b)
{
	int x = *a;
	*a = *b;
	*b = x;
}

int BruteForce::calculateRoad()
{
	int sum = 0;

	//for (int i = 0; i < indexArraySize; i++)
	//{
	//	std::cout << indexArray[i] << ", ";
	//}
	//std::cout << std::endl;

	sum += matrix->adjacencyMatrix[0][indexArray[0]];
	for (int i = 0; i < matrixSize - 1; i++)
		sum += matrix->adjacencyMatrix[indexArray[i]][indexArray[i + 1]];
	sum += matrix->adjacencyMatrix[indexArray[matrixSize - 1]][0];

	return sum;
}

int BruteForce::nextPermutation(int depth)
{
	int i = matrixSize - depth;
	for (int j = i; j < matrixSize; j++) {
		if (depth != 1) {
			swap(&indexArray[i], &indexArray[j]);
			nextPermutation(depth - 1);
			swap(&indexArray[i], &indexArray[j]);
		}
		else {
			int currentRoad = calculateRoad();
			if (currentRoad < smallestRoad) {
				smallestRoad = currentRoad;
				memcpy(smallestRoadArray, indexArray, 4 * matrixSize);
			}

		}
	}
	return smallestRoad;
}

int BruteForce::calculateBruteForce(AdjacencyMatrix* m)
{
	matrix = m;
	matrixSize = m->matrixSize - 1;
	indexArray = new int[matrixSize];
	smallestRoadArray = new int[matrixSize];


	for (int i = 0; i < matrixSize; i++) {
		indexArray[i] = i + 1;
	}

	smallestRoad = INT_MAX;

	smallestRoad = nextPermutation(matrixSize);

	return smallestRoad;
}
