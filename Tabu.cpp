#include "Tabu.h"
#include <ctime>
#include <iostream>


int Tabu::calculateRoad(int* road)
{
	int sum = 0;

	for (int i = 0; i < matrixSize - 1; i++)
		sum += matrix->adjacencyMatrix[road[i]][road[i + 1]];
	sum += matrix->adjacencyMatrix[road[matrixSize - 1]][0];

	return sum;
}

int Tabu::calculateTabu(AdjacencyMatrix* m, double maxTime, int maxTabuSize)
{
	double totalTime = 0;
	matrix = new AdjacencyMatrix(*m);
	matrixSize = matrix->matrixSize;
	this->tabuList = new TabuList(maxTabuSize);
	int roadNotChanged = 0;

	currentRoad = new int[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		currentRoad[i] = i;
	}
	
	bestRoad = new int[matrixSize];
	memcpy(bestRoad, currentRoad, matrixSize * 4);

	int bestRoadDistance = calculateRoad(bestRoad);

	clock_t begin = clock();
	while (totalTime < maxTime)
	{

		currentRoad = getBestCandidate(currentRoad);
		int currentRoadDistance = calculateRoad(currentRoad);

		if (currentRoadDistance < bestRoadDistance)
		{
			memcpy(bestRoad, currentRoad, matrixSize * 4);
			bestRoadDistance = calculateRoad(bestRoad);
			roadNotChanged = 0;
			tabuList->insert(bestChange[0], bestChange[1]);
		}
		else
		{
			roadNotChanged++;
			//tabuList->insert(bestChange[0], bestChange[1]);
		}

		if (roadNotChanged == 100)
		{
			for (int i = 0; i < 100; i++)
				randomSwap();

			roadNotChanged = 0;
			tabuList->clear();
		}

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		totalTime = elapsed_secs;

	}

	tabuList->clear();

	delete[] currentRoad;
	delete matrix;
	return bestRoadDistance;
}

int* Tabu::getBestCandidate(int* road)
{
	int* candidateRoad = new int[matrixSize];
	int* newRoad = new int[matrixSize];
	memcpy(candidateRoad, road, matrixSize * 4);
	int repeats = 0;

	for (int i = 0; i < matrixSize; i++)
	{
		memcpy(newRoad, candidateRoad, matrixSize * 4);

		int randomCity = rand() % (matrixSize - 1) + 1;
		int anotherRandomCity = rand() % (matrixSize - 1) + 1;
		while (randomCity == anotherRandomCity)
			anotherRandomCity = rand() % (matrixSize - 1) + 1;

		swap(&newRoad[randomCity], &newRoad[anotherRandomCity]);

		if (!tabuList->contains(randomCity, anotherRandomCity) && calculateRoad(newRoad) < calculateRoad(candidateRoad))
		{
			memcpy(candidateRoad, newRoad, 4 * matrixSize);
			bestChange[0] = randomCity;
			bestChange[1] = anotherRandomCity;
		}
	}
	delete[] newRoad;
	delete[] road;
	return candidateRoad;
}


void Tabu::randomSwap()
{
	int randomCity = rand() % (matrixSize - 1) + 1;
	int anotherRandomCity = rand() % (matrixSize - 1) + 1;
	while (randomCity == anotherRandomCity)
		anotherRandomCity = rand() % (matrixSize - 1) + 1;

	swap(&currentRoad[randomCity], &currentRoad[anotherRandomCity]);
}

void Tabu::swap(int* a, int* b)
{
	int x = *a;
	*a = *b;
	*b = x;
}
