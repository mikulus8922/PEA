#include "BranchAndBound.h"
#include "PriorityQueue.h"
#include <iostream>

void BranchAndBound::clearDiagonal(AdjacencyMatrix* matrix)
{
    for (int i = 0; i < matrix->matrixSize; i++)
        matrix->adjacencyMatrix[i][i] = INT_MAX;
}

Node* BranchAndBound::createNewNode(AdjacencyMatrix* parentMatrix, int from, int to, int depth, TwoWayList roadList)
{
    Node* node = new Node;

    node->depth = depth;
    node->vertex = to;

    node->roadList = new TwoWayList(roadList);

    node->roadList->pushBack(to);


    AdjacencyMatrix* matrixCopy = new AdjacencyMatrix(*parentMatrix);
    node->reducedMatrix = matrixCopy;

    for (int i = 0; i < node->reducedMatrix->matrixSize && depth != 0; i++) {
        node->reducedMatrix->adjacencyMatrix[from][i] = INT_MAX;
        node->reducedMatrix->adjacencyMatrix[i][to] = INT_MAX;
    }

    node->reducedMatrix->adjacencyMatrix[to][0] = INT_MAX;


    return node;
}

int BranchAndBound::calculateNodeCost(AdjacencyMatrix* matrix)
{
    int cost = 0;

    for (int row = 0; row < matrix->matrixSize; row++) {
        int min = INT_MAX;
        for (int column = 0; column < matrix->matrixSize; column++) {
            if (matrix->adjacencyMatrix[row][column] < min)
                min = matrix->adjacencyMatrix[row][column];
        }
        if (min != 0 && min != INT_MAX) {
            cost += min;
            for (int column = 0; column < matrix->matrixSize; column++)
                if (matrix->adjacencyMatrix[row][column] != INT_MAX)
                    matrix->adjacencyMatrix[row][column] -= min;
        }
    }
    
    for (int column = 0; column < matrix->matrixSize; column++) {
        int min = INT_MAX;
        for (int row = 0; row < matrix->matrixSize; row++) {
            if (matrix->adjacencyMatrix[row][column] < min)
                min = matrix->adjacencyMatrix[row][column];
        }
        if (min != 0 && min != INT_MAX) {
            cost += min;
            for (int row = 0; row < matrix->matrixSize; row++)
                if (matrix->adjacencyMatrix[row][column] != INT_MAX)
                    matrix->adjacencyMatrix[row][column] -= min;
        }
    }
    
    return cost;
}

int BranchAndBound::calculateBranchAndBound(AdjacencyMatrix* matrix)
{
    PriorityQueue priotityQueue;

    AdjacencyMatrix* matrixRoot = new AdjacencyMatrix(*matrix);

    int matrixSize = matrixRoot->matrixSize;

    clearDiagonal(matrixRoot);

    TwoWayList* list = new TwoWayList;
    //Dodaj 0 jako pierwszy wierzcholek w drzewie
    Node* root = createNewNode(matrixRoot, -1, 0, 0, *list);
    root->cost = calculateNodeCost(root->reducedMatrix);
    priotityQueue.push(root);

    while (!priotityQueue.isEmpty()) {
        //Sciagnij wierzcholek z obecnie najkrotsza droga z kolejki
        Node* minNode = priotityQueue.top();
        priotityQueue.pop();
        int from = minNode->vertex;

        //std::cout << minNode->depth << std::endl;

        //Jesli dotarles do liscia drzewa dodaj 0 do listy sciezke zwroc wynik
        if (minNode->depth == matrixSize - 1) {

            minNode->roadList->pushBack(0);

            smallestRoadList = new TwoWayList(*minNode->roadList);

            //print path
            //std::cout << "zrobione" << std::endl;
            lowestCost = minNode->cost;
            break;
        }
        //Dla sprawdzanego wierzcholka utworz wszystkie mozliwe polaczenia z pozostalymi
        //wierzcholkami i dodaj je do kolejki
        for (int to = 0; to < matrixSize; to++) {
            if (minNode->reducedMatrix->adjacencyMatrix[from][to] != INT_MAX) {
                AdjacencyMatrix* matrixChild = new AdjacencyMatrix(*minNode->reducedMatrix);
                Node* child = createNewNode(matrixChild, from, to, minNode->depth + 1, *minNode->roadList);
                child->cost = minNode->cost + minNode->reducedMatrix->adjacencyMatrix[from][to] + calculateNodeCost(child->reducedMatrix);
                priotityQueue.push(child);
            }
        }
        priotityQueue.clearMemory(minNode);
        delete minNode;
    }
    while (!priotityQueue.isEmpty()) {
        Node* minNode = priotityQueue.top();
        priotityQueue.pop();
        priotityQueue.clearMemory(minNode);
        delete minNode;
    }
    return lowestCost;
}
