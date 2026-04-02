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

	
	std::cout<<"Size of grid: ";
	std::cin >> columns >> row;

	Grid g(columns,row);
	g.generateGrid();

	auto pathBFS = p.bfs(g,n);
	std::cout<<std::endl;
	auto pathDFS = p.dfs(g,n);
	std::cout<<std::endl;
	auto pathAstar = p.Astar(g,n);

	p.drawPath(g, pathBFS, n);
	std::cout<<"\n\n";
	p.drawPath(g, pathDFS, n);
	std::cout<<"\n\n";
	p.drawPath(g, pathAstar, n);
}