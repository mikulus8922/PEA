#include "SimulatedAnnealing.h"
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>

#define E 2.71828182845904523536

double SimulatedAnnealing::calculateStartingTemperature(AdjacencyMatrix* matrix)
{
	double temperature;
	int first;
	int second;
	double change = 0;

	for (int i = 0; i < 10000; i++) {

		int* road = new int[roadSize];
		int* newRoad = new int[roadSize];

		for (int j = 0; j < roadSize; j++) {
			road[j] = j;
		}

		std::random_shuffle(&road[0], &road[roadSize]);

		memcpy(newRoad, road, 4 * roadSize);

		int first = rand() % roadSize;
		int second = rand() % roadSize;

		while (first == second)
			second = rand() % roadSize;

		int temp = newRoad[first];
		newRoad[first] = newRoad[second];
		newRoad[second] = temp;


		change += abs(calculateCost(matrix, road) - calculateCost(matrix, newRoad));

		delete[] road;
		delete[] newRoad;
	}

	change = change / 10000;

	temperature = (double)((-1) * change) / std::log(0.99);

	return temperature;
}

void SimulatedAnnealing::randomChange()
{
	int first = rand() % roadSize;
	int second = rand() % roadSize;

	while (first == second)
		second = rand() % roadSize;

	//std::cout << "zamiana:" << first << " - " << second << std::endl;

	memcpy(currnetRoadArray, smallestRoadArray, roadSize * 4);
	int temp = currnetRoadArray[first];
	currnetRoadArray[first] = currnetRoadArray[second];
	currnetRoadArray[second] = temp;
}

double SimulatedAnnealing::calculateProbability(double temperatureCurrent)
{
	double exponent = -((currentCost - smallestCost) / temperatureCurrent);
	return pow(E, exponent);
}

int SimulatedAnnealing::calculateCost(AdjacencyMatrix* matrix, int* road)
{
	int cost = 0;
	
	cost += matrix->adjacencyMatrix[0][road[0]];
	for (int i = 0; i < roadSize - 1; i++) {
		cost += matrix->adjacencyMatrix[road[i]][road[i+1]];
	}
	cost += matrix->adjacencyMatrix[road[roadSize - 1]][0];
	return cost;
}

int SimulatedAnnealing::calculateSimulatedAnnealing(AdjacencyMatrix* matrix, double maxTime, double temperatureCooling, int epoch)
{
	roadSize = matrix->matrixSize - 1;
	smallestRoadArray = new int[roadSize];
	currnetRoadArray = new int[roadSize];
	bestRoadArray = new int[roadSize];

	for (int i = 0; i < roadSize; i++) {
		smallestRoadArray[i] = i + 1;
		currnetRoadArray[i] = i + 1;
		bestRoadArray[i] = i + 1;
	}
	currentCost = calculateCost(matrix, currnetRoadArray);
	smallestCost = currentCost;
	bestCost = smallestCost;

	int temperatureCurrent = calculateStartingTemperature(matrix);
	std::cout << "temp: " << temperatureCurrent << std::endl;
	double totalTime = 0;
	clock_t begin = clock();

	while (totalTime < maxTime) {
		for (int i = 0; i < epoch; i++) {
			randomChange();
			currentCost = calculateCost(matrix, currnetRoadArray);

			if (currentCost < smallestCost || ((double)rand() / (double)RAND_MAX) < calculateProbability(temperatureCurrent)) {
				memcpy(smallestRoadArray, currnetRoadArray, 4 * roadSize);
				smallestCost = currentCost;
			}
			if (currentCost < bestCost) {
				memcpy(bestRoadArray, currnetRoadArray, 4 * roadSize);
				bestCost = currentCost;
			}
		}
		temperatureCurrent *= temperatureCooling;

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		totalTime = elapsed_secs;
	}

	return bestCost;
}

//int SimulatedAnnealing::calculateSimulatedAnnealing(AdjacencyMatrix* matrix, double maxTime, double temperatureCooling, int epoch)
//{
//	roadSize = matrix->matrixSize - 1;
//	smallestRoadArray = new int[roadSize];
//	currnetRoadArray = new int[roadSize];
//	bestRoadArray = new int[roadSize];
//
//	for (int i = 0; i < roadSize; i++) {
//		smallestRoadArray[i] = i + 1;
//		currnetRoadArray[i] = i + 1;
//		bestRoadArray[i] = i + 1;
//	}
//	currentCost = calculateCost(matrix, currnetRoadArray);
//	smallestCost = currentCost;
//	bestCost = smallestCost;
//
//	//int temperatureCurrent = calculateStartingTemperature(matrix);
//	double temperatureCurrent = 100.0;
//
//	double totalTime = 0;
//	clock_t begin = clock();
//
//	for (int k = 0; k < roadSize; k++)
//		std::cout << currnetRoadArray[k] << " ";
//	std::cout << std::endl;
//	std::cout << "koszt: " << currentCost << std::endl;
//	std::cout << std::endl;
//
//	for (int j = 0; j < 2; j++) {
//		std::cout << std::endl;
//		std::cout << "temperatura: " << temperatureCurrent << std::endl;
//
//		for (int i = 0; i < epoch; i++) {
//			randomChange();
//			currentCost = calculateCost(matrix, currnetRoadArray);
//
//			for (int k = 0; k < roadSize; k++)
//				std::cout << currnetRoadArray[k] << " ";
//			std::cout << std::endl;
//			std::cout << "koszt: " << currentCost << std::endl;
//
//			if (currentCost < smallestCost || ((double)rand() / (double)RAND_MAX) < calculateProbability(temperatureCurrent)) {
//				std::cout << "zaakceptuj" << std::endl;
//				memcpy(smallestRoadArray, currnetRoadArray, 4 * roadSize);
//				smallestCost = currentCost;
//			}
//			if (currentCost < bestCost) {
//				memcpy(bestRoadArray, currnetRoadArray, 4 * roadSize);
//				bestCost = currentCost;
//			}
//			std::cout << std::endl;
//		}
//		temperatureCurrent *= temperatureCooling;
//
//		clock_t end = clock();
//		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//		totalTime = elapsed_secs;
//	}
//
//	return bestCost;
//}
