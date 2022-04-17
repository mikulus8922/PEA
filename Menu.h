#pragma once
#include "AdjacencyMatrix.h"


class Menu
{
public:

	Menu();

	void loadMenu();
	void correctnessMenu();
	void performanceMenu();

	void simulatedAnnealingMenu(AdjacencyMatrix* matrix, bool checkPerformance);
	void tabuMenu(AdjacencyMatrix* matrix, bool checkPerformance);

	void geneticMenu(AdjacencyMatrix* matrix, bool checkPerformance);
};

