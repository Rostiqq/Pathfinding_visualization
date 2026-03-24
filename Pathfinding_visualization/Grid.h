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
	void drawGrid() const;
	void generateGrid();
};
