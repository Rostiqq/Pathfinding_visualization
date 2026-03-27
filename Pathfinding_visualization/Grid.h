#pragma once
#include <vector>
#include "Node.h"

class Grid
{
public:
	int HEIGHT;
	int WIDTH;

	std::vector<std::vector<int>> grid;

	Grid(int height, int width);
	int getNeighbour(Node neighbors[4], Node& node);
	void drawGrid() const;
	void generateGrid();
	bool isInside(int x, int y) const;
	bool isWall(int x, int y) const;
};
