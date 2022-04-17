#include "Menu.h"
#include <iostream>
#include "LoadGraphFromFile.h"
#include "LoadGraphRandom.h"
#include "Timer.h"
#include "BruteForce.h"
#include "BranchAndBound.h"
#include "HeldKarp.h"
#include "SimulatedAnnealing.h"
#include "Tabu.h"
#include "GeneticAlgorithm.h"

Menu::Menu() {
}

void Menu::loadMenu() {
	int input;
	do {
		std::cout << "Wybierz tryb pracy programu:" << std::endl;
		std::cout << "1 - Sprawdzenie poprawnosci (wczytywanie danych z pliku)" << std::endl;
		std::cout << "2 - Testy wydajnosci (dane generowane losowo)" << std::endl;
		std::cout << "3 - Zakonczenie pracy programu" << std::endl;

		std::cin >> input;
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			correctnessMenu();
			break;
		case 2:
			performanceMenu();
			break;
		case 3:
			break;
		default:
			std::cout << "Podana opcja nie istnieje" << std::endl;
			break;
		}


	} while (input != 3);

}

void Menu::correctnessMenu() {
	LoadGraphFromFile loadGraphFromFile;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	BruteForce* bruteForce = new BruteForce;
	BranchAndBound* branchAndBound = new BranchAndBound;
	HeldKarp* heldKarp = new HeldKarp;
	Tabu* calculateTabu = new Tabu;


	int road;
	int input;
	do {
		std::cout << "Wybierz tryb pracy programu:" << std::endl;
		std::cout << "1 - Wczytanie danych z pliku" << std::endl;
		std::cout << "2 - Wyswietlenie w formie tablicy" << std::endl;
		std::cout << "3 - Wyswietlenie w formie start-koniec-waga" << std::endl;
		std::cout << "4 - Przetestowanie algorytmu BF" << std::endl;
		std::cout << "5 - Przetestowanie algorytmu B&B" << std::endl;
		std::cout << "6 - Przetestowanie algorytmu DP" << std::endl;
		std::cout << "7 - Przetestowanie algorytmu SA" << std::endl;
		std::cout << "8 - Przetestowanie algorytmu Tabu" << std::endl;
		std::cout << "9 - Przetestowanie algorytmu Genetycznego" << std::endl;
		std::cout << "0 - Powrot" << std::endl;

		std::cin >> input;
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			if (loadGraphFromFile.chooseFile()) {
				if (adjacencyMatrix != nullptr)
					delete adjacencyMatrix;
				adjacencyMatrix = loadGraphFromFile.loadFromFile();
			}
			break;
		case 2:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			adjacencyMatrix->displayMatrixForm();
			break;
		case 3:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			adjacencyMatrix->displayStartEndForm();
			break;
		case 4:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			road = bruteForce->calculateBruteForce(adjacencyMatrix);
			std::cout << "Minimalny cykl: " << road << std::endl;
			std::cout << "0 -> ";
			for(int i = 0; i < bruteForce->matrixSize; i++)
				std::cout << bruteForce->smallestRoadArray[i] << " -> ";
			std::cout << "0" << std::endl;
			break;
		case 5:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			road = branchAndBound->calculateBranchAndBound(adjacencyMatrix);
			std::cout << "Minimalny cykl: " << road << std::endl;
			branchAndBound->smallestRoadList->displayFromFront();
			break;
		case 6:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			road = heldKarp->calculateHeldKarp(adjacencyMatrix);
			std::cout << "Minimalny cykl: " << road << std::endl;
			for (int i = 0; i < heldKarp->matrixSize; i++)
				std::cout << heldKarp->smallestRoadArray[i] << " -> ";
			std::cout << "0" << std::endl;
			break;
		case 7:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			simulatedAnnealingMenu(adjacencyMatrix, 0);
			break;
		case 8:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			tabuMenu(adjacencyMatrix, 0);
		case 9:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			geneticMenu(adjacencyMatrix, 0);
			break;
		case 0:
			break;
		default:
			std::cout << "Podana opcja nie istnieje" << std::endl;
			break;
		}

	} while (input != 0);

	if (adjacencyMatrix != nullptr)
		delete adjacencyMatrix;

}

void Menu::performanceMenu()
{
	LoadGraphRandom loadGraphRandom;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	BruteForce* bruteForce = new BruteForce;
	BranchAndBound* branchAndBound = new BranchAndBound;
	HeldKarp* heldKarp = new HeldKarp;
	LoadGraphFromFile loadGraphFromFile;

	Timer timer;

	int matrixSize = 10;
	double time = 0;
	double timeSum;
	int input;
	do {
		std::cout << "Wybierz tryb pracy programu:" << std::endl;
		std::cout << "1 - Zmien rozmiar generowanych grafow" << std::endl;
		std::cout << "2 - Przetestowanie algorytmu BF" << std::endl;
		std::cout << "3 - Przetestowanie algorytmu B&B" << std::endl;
		std::cout << "4 - Przetestowanie algorytmu DP" << std::endl;
		std::cout << "5 - Przetestowanie algorytmu SA" << std::endl;
		std::cout << "6 - Przetestowanie algorytmu Tabu" << std::endl;
		std::cout << "7 - Przetestowanie algorytmu Genetycznego" << std::endl;
		std::cout << "9 - Wczytaj dane z pliku (SA i Tabu)" << std::endl;
		std::cout << "0 - Powrot" << std::endl;

		std::cin >> input;
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			std::cout << "Wpisz nowy rozmiar:" << std::endl;
			std::cin >> matrixSize;
			std::cout << std::endl;
			break;
		case 2:
			timeSum = 0;
			for (int i = 0; i < 100; i++) {
				adjacencyMatrix = loadGraphRandom.generateRandomGraph(matrixSize);
				std::cout << i + 1 << ": ";
				timer.startTimer();
				bruteForce->calculateBruteForce(adjacencyMatrix);
				timer.stopTimer();
				time = timer.calculateTime();
				std::cout << time << std::endl;
				timeSum += time;
				delete adjacencyMatrix;
			}
			std::cout << "Sredni czas BF: " << timeSum / 100 << std::endl;
			break;
		case 3:
			timeSum = 0;
			for (int i = 0; i < 100; i++) {
				adjacencyMatrix = loadGraphRandom.generateRandomGraph(matrixSize);
				std::cout << i + 1 << ": ";
				timer.startTimer();
				branchAndBound->calculateBranchAndBound(adjacencyMatrix);
				timer.stopTimer();
				time = timer.calculateTime();
				std::cout << time << std::endl;
				timeSum += time;
				delete adjacencyMatrix;
			}
			std::cout << "Sredni czas B&B: " << timeSum / 100 << std::endl;
			break;
		case 4:
			timeSum = 0;
			for (int i = 0; i < 100; i++) {
				adjacencyMatrix = loadGraphRandom.generateRandomGraph(matrixSize);
				std::cout << i + 1 << ": ";
				timer.startTimer();
				heldKarp->calculateHeldKarp(adjacencyMatrix);
				timer.stopTimer();
				time = timer.calculateTime();
				std::cout << time << std::endl;
				timeSum += time;
				delete adjacencyMatrix;
			}
			std::cout << "Sredni czas HK: " << timeSum / 100 << std::endl;
			break;
		case 5:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			simulatedAnnealingMenu(adjacencyMatrix, 1);
			break;
		case 6:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			tabuMenu(adjacencyMatrix, 1);
			break;
		case 7:
			if (adjacencyMatrix == nullptr) {
				std::cout << "Nie zaladowano danych" << std::endl;
				break;
			}
			geneticMenu(adjacencyMatrix, 1);
			break;
		case 9:
			if (loadGraphFromFile.chooseFile()) {
				if (adjacencyMatrix != nullptr)
					delete adjacencyMatrix;
				adjacencyMatrix = loadGraphFromFile.loadFromFile();
			}
			break;
		case 0:
			break;
		default:
			std::cout << "Podana opcja nie istnieje" << std::endl;
			break;
		}

	} while (input != 0);

}

void Menu::simulatedAnnealingMenu(AdjacencyMatrix* matrix, bool checkPerformance)
{
	double maxTime = 1.0;
	double temperatureCooling = 0.99;
	int epoch = 100;
	int input;
	int road;

	SimulatedAnnealing* simulatedAnnealing = new SimulatedAnnealing;

	do {
		std::cout << "Wybierz tryb pracy programu:" << std::endl;
		std::cout << "1 - Zmien czas wykonwyania algorytmu" << std::endl;
		std::cout << "2 - Zmien temperature chlodzenia" << std::endl;
		std::cout << "3 - Zmien dlugosc epoki" << std::endl;
		std::cout << "4 - Przetestowanie algorytmu SA" << std::endl;
		std::cout << "0 - Powrot" << std::endl;

		std::cin >> input;
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			std::cout << "Wpisz czas wykonwyania algorytmu:" << std::endl;
			std::cin >> maxTime;
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "Wpisz temperature chlodzenia:" << std::endl;
			std::cin >> temperatureCooling;
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "Wpisz dlugosc epoki:" << std::endl;
			std::cin >> epoch;
			std::cout << std::endl;
			break;
		case 4:
			if (!checkPerformance)
			{
				road = simulatedAnnealing->calculateSimulatedAnnealing(matrix, maxTime, temperatureCooling, epoch);
				std::cout << "Minimalny cykl: " << road << std::endl;
				std::cout << "0 -> ";
				for (int i = 0; i < simulatedAnnealing->roadSize; i++)
					std::cout << simulatedAnnealing->bestRoadArray[i] << " -> ";
				std::cout << "0" << std::endl;
			}
			else {
				double sum = 0;
				for (int i = 0; i < 5; i++) {
					road = simulatedAnnealing->calculateSimulatedAnnealing(matrix, maxTime, temperatureCooling, epoch);
					std::cout << i + 1 << ": " << road << std::endl;
					sum += road;
				}
				std::cout << "Sredni wynik SA: " << sum / 5 << std::endl;
			}

			break;
		case 0:
			break;
		default:
			std::cout << "Podana opcja nie istnieje" << std::endl;
			break;
		}

	} while (input != 0);
}

void Menu::tabuMenu(AdjacencyMatrix* matrix, bool checkPerformance)
{
	double maxTime = 1.0;
	int tabuList = 100;
	int input;
	int road;

	Tabu* tabu = new Tabu;

	do {
		std::cout << "Wybierz tryb pracy programu:" << std::endl;
		std::cout << "1 - Zmien czas wykonwyania algorytmu" << std::endl;
		std::cout << "2 - Zmien dlugosc listy tabu" << std::endl;
		std::cout << "3 - Przetestowanie algorytmu Tabu" << std::endl;
		std::cout << "0 - Powrot" << std::endl;

		std::cin >> input;
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			std::cout << "Wpisz czas wykonwyania algorytmu:" << std::endl;
			std::cin >> maxTime;
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "Wpisz temperature chlodzenia:" << std::endl;
			std::cin >> tabuList;
			std::cout << std::endl;
			break;
		case 3:
			if (!checkPerformance)
			{
				road = tabu->calculateTabu(matrix, maxTime, tabuList);
				std::cout << "Minimalny cykl: " << road << std::endl;
				for (int i = 0; i < tabu->matrixSize; i++)
					std::cout << tabu->bestRoad[i] << " -> ";
				std::cout << "0" << std::endl;
			}
			else {
				double sum = 0;
				for (int i = 0; i < 5; i++) {
					road = tabu->calculateTabu(matrix, maxTime, tabuList);
					std::cout << i + 1 << ": " << road << std::endl;
					sum += road;
				}
				std::cout << "Sredni wynik Tabu: " << sum / 5 << std::endl;
			}

			break;
		case 0:
			break;
		default:
			std::cout << "Podana opcja nie istnieje" << std::endl;
			break;
		}

	} while (input != 0);

}

void Menu::geneticMenu(AdjacencyMatrix* matrix, bool checkPerformance)
{
	double maxTime = 10.0;
	int populationSize = 10;
	float mutationPropability = 0.01;
	float crossoverPropability = 0.8;
	int mutationType = 1;
	int road;

	int input;

	GeneticAlgorithm* genetic = new GeneticAlgorithm;

	do {
		std::cout << "Wybierz tryb pracy programu:" << std::endl;
		std::cout << "1 - Zmien czas wykonwyania algorytmu" << std::endl;
		std::cout << "2 - Zmien rozmiar populacji" << std::endl;
		std::cout << "3 - Zmien prawdopodobienstwo mutacji" << std::endl;
		std::cout << "4 - Zmien prawdopodobienstwo krzyzowania" << std::endl;
		std::cout << "5 - Zmien typ mutacji" << std::endl;
		std::cout << "6 - Przetestowanie algorytmu genetycznego" << std::endl;
		std::cout << "0 - Powrot" << std::endl;

		std::cin >> input;
		std::cout << std::endl;

		switch (input)
		{
		case 1:
			std::cout << "Wpisz czas wykonwyania algorytmu:" << std::endl;
			std::cin >> maxTime;
			std::cout << std::endl;
			break;
		case 2:
			std::cout << "Wpisz rozmiar populacji:" << std::endl;
			std::cin >> populationSize;
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "Wpisz prawdopodobienstwo mutacji:" << std::endl;
			std::cin >> mutationPropability;
			std::cout << std::endl;
			break;
		case 4:
			std::cout << "Wpisz prawdopodobienstwo krzyzowania:" << std::endl;
			std::cin >> crossoverPropability;
			std::cout << std::endl;
			break;
		case 5:
			std::cout << "Wpisz typ mutacji (0 - Swap; 1 - Insert):" << std::endl;
			std::cin >> mutationType;
			std::cout << std::endl;
			break;
		case 6:
			if (!checkPerformance)
			{
				road = genetic->calculateGeneticAlgorithm(matrix, populationSize, mutationPropability, crossoverPropability, mutationType, maxTime);
				std::cout << "Minimalny cykl: " << road << std::endl;
				for (int i = 0; i < genetic->matrixSize; i++)
					std::cout << genetic->resultRoad[i] << " -> ";
				std::cout << "0" << std::endl;
			}
			else {
				double sum = 0;
				for (int i = 0; i < 10; i++) {
					road = genetic->calculateGeneticAlgorithm(matrix, populationSize, mutationPropability, crossoverPropability, mutationType, maxTime);
					std::cout << i + 1 << ": " << road << std::endl;
					sum += road;
				}
				std::cout << "Sredni wynik GA: " << sum / 10 << std::endl;
			}

			break;
		case 0:
			break;
		default:
			std::cout << "Podana opcja nie istnieje" << std::endl;
			break;
		}

	} while (input != 0);


}
