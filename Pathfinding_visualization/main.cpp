#include <iostream>
#include <vector>
#include "Grid.h"

int main() {
	int columns;
	int row;
	std::cout << "Size of grid: ";
	std::cin >> columns >> row;

	Grid g(columns, row);
	g.generateGrid();
	g.drawGrid();
	std::cout << std::endl;
}