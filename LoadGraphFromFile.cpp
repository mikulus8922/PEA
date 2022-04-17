#include "LoadGraphFromFile.h"
#include <iostream>


LoadGraphFromFile::LoadGraphFromFile() {
	filePath = "";
}


LoadGraphFromFile::~LoadGraphFromFile() {

}


bool LoadGraphFromFile::chooseFile() {
	string tempFilePath = "";

	std::cout << "Podaj sciezke pliku" << std::endl;
	std::cin >> tempFilePath;
	std::cout << std::endl;

	fileStream.open(tempFilePath);

	while (!fileStream.is_open()) {
		std::cout << "Plik nie zostal otwarty." << std::endl;
		std::cout << "Podaj nowa sciezke pliku lub wpisz \"0\" by wyjsc" << std::endl;
		std::cin >> tempFilePath;
		std::cout << std::endl;
		if (tempFilePath == "0") {
			return false;
		}
		else {
			fileStream.open(tempFilePath);
		}
	}

	filePath = tempFilePath;

	fileStream.close();
	return true;
}

AdjacencyMatrix* LoadGraphFromFile::loadFromFile() {

	fileStream.open(filePath);


	string word = "";
	

	while (word != "DIMENSION:") {
		fileStream >> word;
	}
		
	fileStream >> word;
	AdjacencyMatrix* adjecancyMatrix = new AdjacencyMatrix(std::stoi(word));

	while (word != "EDGE_WEIGHT_SECTION") {
		fileStream >> word;
	}

	for (int i = 0; i < adjecancyMatrix->matrixSize; i++) {
		for (int j = 0; j < adjecancyMatrix->matrixSize; j++) {
			fileStream >> word;
			adjecancyMatrix->addLink(i, j, std::stoi(word));
		}

	}

	fileStream.close();

	return adjecancyMatrix;
}
