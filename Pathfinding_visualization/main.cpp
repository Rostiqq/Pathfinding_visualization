#include <iostream>
#include <vector>
#include "Grid.h"
#include "Pathfinding.h"

int main()
{
	int columns;
	int row;
	Pathfinding p;
	Node n{0, 0};

	std::cout << "Size of grid: ";
	std::cin >> columns >> row;
	std::cout << std::endl;

	Grid g(columns, row);
	g.generateGrid();
	g.drawGrid();
	std::cout << std::endl;
	p.bfs(g, n);

	auto pathBFS = p.bfs(g, n);
	p.drawPath(g, pathBFS, n);
	std::cout << std::endl;

	auto pathDFS = p.dfs(g, n);
	p.drawPath(g, pathDFS, n);
}