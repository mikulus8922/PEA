#include "GeneticAlgorithm.h"

#include <random>

#include <iostream>


int* GeneticAlgorithm::generateStartingRoad()
{
	int* road = new int[matrixSize];

	for (int i = 0; i < matrixSize; i++)
		road[i] = i;

	return road;
}


void GeneticAlgorithm::generateStartingPopulation() {


	for (int i = 0; i < populationSize; i++) {


		population[i] = generateStartingRoad();

	}

	calculatePopulationFitness();
}

void GeneticAlgorithm::calculatePopulationFitness() {

	for (int i = 0; i < populationSize; i++) {
		fitness[i] = calculateRoad(population[i]);
	}
}

int GeneticAlgorithm::calculateRoad(int* road)
{
	int cost = 0;

	cost += matrix->adjacencyMatrix[0][road[1]];
	for (int i = 1; i < matrixSize - 1; i++) {
		cost += matrix->adjacencyMatrix[road[i]][road[i + 1]];
	}
	cost += matrix->adjacencyMatrix[road[matrixSize - 1]][0];
	return cost;
}

int GeneticAlgorithm::rouletteWheelSelection() {
	int worstFitness = 0;
	for (int i = 0; i < populationSize; i++)
		if (fitness[i] > worstFitness)
			worstFitness = fitness[i];

	// Oblicz alternatywny koszt kazdego osobnika z populacji,
	// rozumiane jako roznica miedzy kosztem danego osobnika
	// a najgorszym osobnikiem w populacji
	int*  alt_fitness = new int[populationSize];
	for (int i = 0; i < populationSize; i++) {
		alt_fitness[i] = (-(fitness[i] - worstFitness) + 1);
	}

	int totalAltSumOfAllFitnesses = 0;

	// Oblicz sume kosztow wszystkich osobników w populacji
	for (int i = 0; i < populationSize; i++)
		totalAltSumOfAllFitnesses += alt_fitness[i];

	int r = rand() % totalAltSumOfAllFitnesses;

	// Wylosuj osobnika
	int counting_s = 0;
	for (int i = 0; i < populationSize; i++) {
		counting_s += alt_fitness[i];
		if (counting_s > r) {
			delete[] alt_fitness;
			return i;
		}
	}
}

void GeneticAlgorithm::generateNewPopulation() {


	// Dla wszystkich osobnikow oprocz ostatniego
	for (int i = 0; i < populationSize - 1; i++) {

		// Wylosowanie pierwszego osobnika
		int index1 = rouletteWheelSelection();

		// Losowanie liczby z przedzialu od 0 do 1
		float chance = rand() % 100001;
		chance /= 100000;

		// Jesli wylosowana liczba jest mniejsza od prawdopodobienstwa
		// krzyzowania to wylosuj drugiego osobnika i ich skrzyzuj
		if (chance < crossoverProbability) {
			int index2 = rouletteWheelSelection();
			while (index1 == index2)
				index2 = rouletteWheelSelection();
			int* crossovered_chromosome = crossover(population[index1], population[index2]);

			for (int j = 0; j < matrixSize; j++) {
				new_population[i][j] = crossovered_chromosome[j];
			}

			delete[] crossovered_chromosome;
		}
		else {
			// Jesli ma nie dojsc do krzyzowania to skopiuj
			// pierwszego wylosowanego osobnika
			for (int j = 0; j < matrixSize; j++) {
				new_population[i][j] = population[index1][j];
			}
		}
	}


	// Dla ostatniego osobnika nowej populacji
	// wybierz najlepszego osobnika ze starej populacji
	// i go skopiuj (tzw. elityzm)
	int* elitism_chromosome = nullptr;
	int elitism_chromosome_fitness = std::numeric_limits<int>::max();
	for (int i = 0; i < populationSize; i++) {
		if (fitness[i] < elitism_chromosome_fitness) {
			elitism_chromosome_fitness = fitness[i];
			elitism_chromosome = population[i];
		}
	}

	for (int i = 0; i < matrixSize; i++) {
		new_population[populationSize - 1][i] = elitism_chromosome[i];
	}


	// Mutacja wszystkich nowych osobnikow (oprocz wyroznionego w ramach elityzmu)
	for (int i = 0; i < populationSize - 1; i++) {
		for (int j = 1; j < matrixSize; j++) {

			// Losowanie liczby z przedzialu od 0 do 1
			float chance = rand() % 100001;
			chance /= 100000;

			// Jesli wylosowana liczba jest mniejsza od prawdopodobienstwa
			// krzyzowania to dokonaj wybranej mutacji
			if (chance < mutationProbability) {

				int city2 = (rand() % (matrixSize - 1)) + 1;

				while (j == city2)
					city2 = (rand() % (matrixSize - 1)) + 1;

				if (mutationType == 0) {
					// mutacja typu SWAP
					std::swap(new_population[i][j], new_population[i][city2]);
				}
				else if (mutationType == 1) {
					// mutacja typu INSERT
					int popped = new_population[i][j];


					//j delete place
					int* popped_population = new int[matrixSize - 1];
					int l = 0;
					for (int k = 0; k < matrixSize; k++)
					{
						if (k != j) {
							popped_population[l] = new_population[i][k];
							l++;
						}
					}
					// city 2 insert place
					l = 0;
					for (int k = 0; k < matrixSize; k++)
					{
						if (k != city2) {
							new_population[i][k] = popped_population[k - l];
						}
						else {
							new_population[i][k] = popped;
							l = 1;
						}
					}
					delete[] popped_population;
				}
			}
		}
	}

	// Przepisanie nowej populacji do tabeli starej populacji
	for (int i = 0; i < populationSize; i++) {
		for (int j = 0; j < matrixSize; j++)
		{
			population[i][j] = new_population[i][j];
		}
	}

	// Obliczenie kosztow poszczegolnych osobnikow
	calculatePopulationFitness();

}

int* GeneticAlgorithm::crossover(int* parent1, int* parent2) {

	int* child = new int[matrixSize];

	// Indeks do ktorego bedzie kopiowany pierwszy rodzic
	int point = (rand() % (matrixSize - 1)) + 1;

	// Skopiuj czesc "genomu" pierwszego rodzica
	for (int i = 0; i < point; i++)
		child[i] = parent1[i];

	// Skopiuj pozostala czesc genomu od drugiego rodzica
	int insert_point = point;
	for (int j = 1; j < matrixSize; j++) {
		int x = parent2[j];

		bool next_number = false;
		for (int k = 0; k < point; k++) {
			if (x == child[k]) {
				next_number = true;
				break;
			}
		}

		if (next_number)
			continue;

		child[insert_point] = x;
		insert_point++;
	}

	return child;
}


int GeneticAlgorithm::calculateGeneticAlgorithm(AdjacencyMatrix* matrix, int populationSize, float mutationProbability, float crossoverProbability, int mutationType, float maxTime) {

	this->matrix = matrix;
	this->matrixSize = matrix->matrixSize;
	this->populationSize = populationSize;
	this->mutationProbability = mutationProbability;
	this->crossoverProbability = crossoverProbability;
	this->mutationType = mutationType;


	population = new int* [populationSize];
	for (int i = 0; i < populationSize; i++) {
		population[i] = new int[matrixSize];
	}
	new_population = new int* [populationSize];
	for (int i = 0; i < populationSize; i++) {
		new_population[i] = new int[matrixSize];
	}

	fitness = new int[populationSize];

	generateStartingPopulation();

	double totalTime = 0;
	clock_t begin = clock();

	while (totalTime < maxTime) {

		generateNewPopulation();

		//std::cout << calculateRoad(population[populationSize - 1]) << std::endl;

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		totalTime = elapsed_secs;
	}

	result = std::numeric_limits<int>::max();

	// Po zakonczeniu dzialania algorytmu zapisz najlepszy cykl
	for (int i = 0; i < populationSize; i++) {
		if (fitness[i] < result) {
			result = fitness[i];
			resultRoad = population[i];
		}
	}

	return result;
}
