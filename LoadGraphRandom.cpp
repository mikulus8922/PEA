#include "LoadGraphRandom.h"
#include <random>

LoadGraphRandom::LoadGraphRandom()
{
}

AdjacencyMatrix* LoadGraphRandom::generateRandomGraph(int size)
{
	AdjacencyMatrix* adjacencyMatrix = new AdjacencyMatrix(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j)
				adjacencyMatrix->addLink(i, j, 10000);
			else
				adjacencyMatrix->addLink(i, j, rand() % 1000 + 1);
		}
	}

	return adjacencyMatrix;
}
