#pragma once
#include "AdjacencyMatrix.h"


class GeneticAlgorithm
{
private:
	// rozmiar populacji
	int populationSize;
	// prawdopodobienstwo mutacji
	float mutationProbability;
	// prawdopodobienstwo krzyzowania
	float crossoverProbability;
	// typ mutacji (0-swap 1-insert)
	int mutationType;

	// tablica przechowujaca koszty grafu
	AdjacencyMatrix* matrix;

	// tablica dwuwymiarowa przechowujaca populacje
	int** population;
	// tablica przechowujaca koszty poszczegolnych osobnikow
	int* fitness;

	// tablica dwuwymiarowa przechowujaca nowa populacje
	int** new_population;

	// ostateczny koszt
	int result;

	/// <summary>
	/// Funkcja pomocnicza generujaca poczatkowa sciezke danego osobnika
	/// </summary>
	/// <returns></returns>
	int* generateStartingRoad();
	/// <summary>
	/// Funkcja pomocnicza generujaca poczatkowa populacje
	/// </summary>
	void generateStartingPopulation();
	/// <summary>
	/// Funkcja pomocnicza obliczajaca koszta osobnikow w obecnej populacji
	/// i zapisujaca je w tablicy fitness
	/// </summary>
	void calculatePopulationFitness();
	/// <summary>
	/// Funkcja pomocnicza obliczajaca koszt danego osobnika
	/// </summary>
	/// <param name="vertices"></param>
	/// <returns></returns>
	int calculateRoad(int* vertices);

	/// <summary>
	/// Funkcja pomocnicza losujaca danego osobnika za pomoca
	/// wyboru ruletkowego, gdzie lepsze osobniki maja wieksze szanse
	/// na zostanie wybranym
	/// </summary>
	/// <returns></returns>
	int rouletteWheelSelection();

	/// <summary>
	/// Funckja pomocnicza bedaca glowna petla algorytmu
	/// </summary>
	void generateNewPopulation();

	/// <summary>
	/// Funkcja pomocnicza majaca na celu skrzyzowanie dwoch osobnikow
	/// podanych w parametrach z pomoca algorytmu
	/// "single point crossover"
	/// </summary>
	/// <param name="parent1"></param>
	/// <param name="parent2"></param>
	/// <returns></returns>
	int* crossover(int* parent1, int* parent2);
public:
	// rozmiar grafu
	int matrixSize;
	// tablica przechowywujaca poszczegolne wierzcholki ostatecznego cyklu
	int* resultRoad;

	/// <summary>
	/// Glowna funkcja algorytmu
	/// </summary>
	/// <param name="matrix"></param>
	/// <param name="populationSize"></param>
	/// <param name="mutationProbability"></param>
	/// <param name="crossoverProbability"></param>
	/// <param name="mutationType"></param>
	/// <param name="maxTime"></param>
	/// <returns></returns>
	int calculateGeneticAlgorithm(AdjacencyMatrix* matrix, int populationSize, float mutationProbability, float crossoverProbability, int mutationType, float maxTime);
};