#include "Grid.h"
#include <iostream>
#include <random>

Grid::Grid(int height, int width) {

    HEIGHT = height;
    WIDTH = width;

    grid.resize(HEIGHT, std::vector<int>(WIDTH));
}

void Grid::drawGrid() const {
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == 0 && y == 0)
			{
				std::cout << "S ";
			}
			else if (x == WIDTH -1 && y == HEIGHT -1)
			{
				std::cout << "E ";
			}
			else
			{
				std::cout << grid[y][x] << " ";
			}
		}
		std::cout << std::endl;
	}
}

void Grid::generateGrid()  {
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> dist(0, 1);
	
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if ((x == 0 && y == 0) || (x == WIDTH -1 && y == HEIGHT -1))
			{
				grid[y][x] = 0;
			}
			else
			{
				grid[y][x] = dist(gen);
			}
		}
		std::cout << std::endl;
	}
}