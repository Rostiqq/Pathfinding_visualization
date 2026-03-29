#include "Grid.h"
#include <iostream>
#include <random>

Grid::Grid(int height, int width)
{

	HEIGHT = height;
	WIDTH = width;

	grid.resize(HEIGHT, std::vector<int>(WIDTH));
}

void Grid::drawGrid() const
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == 0 && y == 0)
			{
				std::cout << "S ";
			}
			else if (x == WIDTH - 1 && y == HEIGHT - 1)
			{
				std::cout << "E ";
			}
			else
			{
				if (grid[y][x] == 0)
				{
					std::cout << ". ";
				}
				else
				{
					std::cout << "| ";
				}
			}
		}
		std::cout << std::endl;
	}
}

void Grid::generateGrid()
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> dist(0, 99);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if ((x == 0 && y == 0) || (x == WIDTH - 1 && y == HEIGHT - 1))
			{
				grid[y][x] = 0;
			}
			else
			{
				if (dist(gen) <= 24)
				{
					grid[y][x] = 1;
				}
				else
				{
					grid[y][x] = 0;
				}
			}
		}
	}
}

bool Grid::isInside(int x, int y) const
{
	return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Grid::isWall(int x, int y) const
{
	return grid[y][x] == 1;
}

int Grid::getNeighbour(Node neighbors[4], Node &node)
{
	int count = 0;
	int dx[4] = {1, -1, 0, 0};
	int dy[4] = {0, 0, 1, -1};

	for (int i = 0; i < 4; i++)
	{
		int nx = node.x + dx[i];
		int ny = node.y + dy[i];

		if (!isInside(nx, ny))
			continue;
		if (isWall(nx, ny))
			continue;

		neighbors[count++] = Node{nx, ny};
	}
	return count;
}
