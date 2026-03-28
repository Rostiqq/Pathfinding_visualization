#include <iostream>
#include <vector>
#include "Grid.h"
#include "Pathfinding.h"

int main() {
	int columns;
	int row;
	Pathfinding p;
	Node n{ 0,0 };

	std::cout << "Size of grid: ";
	std::cin >> columns >> row;
	std::cout << std::endl;

	Grid g(row,columns);
	g.generateGrid();
	g.drawGrid();

	p.bfs(g,n);
}