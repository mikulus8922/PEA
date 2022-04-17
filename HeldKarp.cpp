#include "HeldKarp.h"
#include <map>
#include <iostream>

using std::map;
using std::pair;

void HeldKarp::calculateAllSets(int setSize, int numberOfVertices, int* vertices, vector<set<int>>* allSets, set<int>currentSet)
{
	if (setSize == numberOfVertices)
		return;

	//Dodaj podzbior do wektora o indeksie rownym dlugosci podzbioru do zbioru wszystkich setow
	allSets[currentSet.size()].push_back(currentSet);

	//Glowna rekurencyjna petla odpowiedzialna za utworzenie wszystkich permutacji w currentSet
	for (int i = setSize; i < numberOfVertices; i++) {
		currentSet.insert(vertices[i]);
		calculateAllSets(i + 1, numberOfVertices, vertices, allSets, currentSet);
		currentSet.erase(currentSet.find(vertices[i]));
	}

	return;
}


int HeldKarp::calculateHeldKarp(AdjacencyMatrix* matrix)
{
	matrixSize = matrix->matrixSize;

	if (matrixSize == 0)
		return 0;

	minCost = INT_MAX;

	

	//Zadeklaruj tablice dynamiczna ktora bedzie przechowywac wszystkie mozliwe podzbiory
	vector<set<int>>* allSets = new vector<set<int>>[matrixSize];

	//Stworz tablice zawierajaca indeksy wszystkich wierzcholkow oprocz poczatkowego
	int* vertices = new int[matrixSize - 1];
	for (int i = 0; i < matrixSize - 1; i++) {
		vertices[i] = i + 1;
	}

	set<int> currentSet;
	//Wygeneruj wszystkie podzbiory
	calculateAllSets(0, matrixSize, vertices, allSets, currentSet);

	//Mapa rzutujaca pare podzbior - wierzcholek na koszt - rodzic
	map <pair<set<int>, int>, pair<int, int>> heldKarpMap;

	//Oblicz wartosci dla pierwszej iteracji (podzbiory dlugosci 1)
	for (int subsetIndex = 0; subsetIndex < allSets[1].size(); subsetIndex++) {

		//Stworz 2 nowe pary wykorzystywane w mapie
		pair<set<int>, int> subsetEndPair;
		pair<int, int> costParentPair;
		//Przypisz odpowiedni podzbior
		subsetEndPair.first = allSets[1][subsetIndex];
		//Przypisz numer wierzcholka
		subsetEndPair.second = subsetIndex + 1;
		//Przypisz koszt sprawdzanego wierzcholka
		costParentPair.first = matrix->adjacencyMatrix[0][subsetIndex + 1];
		//Oznacz wierzcholek poczatkowy (0) jako rodzica
		costParentPair.second = 0;
		//Zmapuj costParentPair na subsetVertexPair
		heldKarpMap[subsetEndPair] = costParentPair;
	}

	//Petla wybierajaca odpowiedni rozmiar podzrioru
	for (int subsetSize = 2; subsetSize < matrixSize; subsetSize++) {

		//Petla wybierajaca odpowiedni podzbior
		for (int subsetIndex = 0; subsetIndex < allSets[subsetSize].size(); subsetIndex++) {

			//Petla wybierajaca 1 wierzcholek z podzbioru
			for (int vertexTo : allSets[subsetSize][subsetIndex]) { 

				int min = INT_MAX;
				int vertexParent = -1;

				//Petla wybierajaca 2 wierzcholek z podzbioru
				for (int vertexFrom : allSets[subsetSize][subsetIndex]) {
					if (vertexTo != vertexFrom) {


						//Skopiuj podzbior i usun sprawdzany wierzcholek
						set<int> tempSet = allSets[subsetSize][subsetIndex];
						tempSet.erase(vertexTo);

						//Stworz 2 nowe pary wykorzystywane w mapie
						pair <set<int>, int> subsetEndPair;
						pair <int, int> costParentPair;

						//Przypisz odpowiedni podzbior
						subsetEndPair.first = tempSet;
						//Przypisz numer wierzcholka
						subsetEndPair.second = vertexFrom;
						//Przypisz odpowiedni costParentPair bedacy wartoscia klucza subsetEndPair
						costParentPair = heldKarpMap[subsetEndPair];
						//Oblicz nowy koszt
						int cost = matrix->adjacencyMatrix[vertexFrom][vertexTo] + costParentPair.first;

						//Jesli znaleziono mniejszy dystans przypisz odpowiedni wierzcholek jako rodzica wraz z jego dystansem
						if (cost < min) {
							min = cost;
							vertexParent = vertexFrom;
						}

						//Przypisz odpowiedni podzbior
						subsetEndPair.first = allSets[subsetSize][subsetIndex];
						//Przypisz numer wierzcholka
						subsetEndPair.second = vertexTo;
						
						//Przypisz minimalny koszt
						costParentPair.first = min;
						//Przypisz rodzica
						costParentPair.second = vertexParent;
						//Zmapuj costParentPair na subsetVertexPair
						heldKarpMap[subsetEndPair] = costParentPair;

					}

				}
			}
		}
	}


	pair<set<int>, int> finalPair;

	//Przypisz ostatnia pare do mapy
	for (int i = 1; i < matrixSize; i++) {
		pair<set<int>, int> subsetEndPair;
		subsetEndPair.first = allSets[matrixSize - 1][0];
		subsetEndPair.second = i;

		int tempDistance = heldKarpMap[subsetEndPair].first + matrix->adjacencyMatrix[i][0];

		if (tempDistance < minCost) {
			minCost = tempDistance;
			finalPair = subsetEndPair;
		}
	}

	pair<int, int> costParentPair;
	smallestRoadArray = new int[matrixSize];

	//Zapisanie ostatecznej sciezki
	int i = matrixSize - 1;
	do {
		costParentPair = heldKarpMap[finalPair];
		smallestRoadArray[i] = finalPair.second;
		currentSet = finalPair.first;
		currentSet.erase(finalPair.second);
		finalPair.first = currentSet;
		finalPair.second = costParentPair.second;
		i--;
	} while (i >= 0);


	//Usuniecie tablicy z wierzcholkami
	delete[] vertices;

	//Usuniecie wszystkich podzbiorow
	for (int k = 0; k < matrixSize; k++) {
		for (int i = 0; i < allSets[k].size(); i++) {
			allSets[k].clear();
		}
	}
	delete[] allSets;

	return minCost;
}
