#include <iostream>
#include <vector>
#include "Grid.h"
#include "Pathfinding.h"
#include "Cell.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window;
	int windowHeight = 400;
	int windowWidth = 600;
	int columns;
	int rows;
	Pathfinding p;
	Node n{0, 0};

	std::cout << "Size of grid: ";
	std::cin >> columns >> rows;

	Grid g(columns, rows);
	g.generateGrid();

	float cellSizeX = windowWidth / float(columns);
	float cellSizeY = windowHeight / float(rows);
	float cellSize = std::min(cellSizeX, cellSizeY);

	window.create(sf::VideoMode(columns * cellSize, rows * cellSize), "PATH", sf::Style::None);
	/*
		auto pathBFS = p.bfs(g, n);
		std::cout << std::endl;
		auto pathDFS = p.dfs(g, n);
		std::cout << std::endl;
		auto pathAstar = p.Astar(g, n);

		p.drawPath(g, pathBFS, n);
		std::cout << "\n\n";
		p.drawPath(g, pathDFS, n);
		std::cout << "\n\n";
		p.drawPath(g, pathAstar, n);
	*/

	std::vector<std::vector<Cell>> cells;
	cells.resize(g.HEIGHT, std::vector<Cell>(g.WIDTH));

	for (int y = 0; y < g.HEIGHT; y++)
	{
		for (int x = 0; x < g.WIDTH; x++)
		{
			cells[y][x].shape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
			cells[y][x].shape.setSize(sf::Vector2f(cellSize, cellSize));

			if (x == 0 && y == 0)
			{
				cells[y][x].setState(State::Start);
			}
			else if (x == g.WIDTH - 1 && y == g.HEIGHT - 1)
			{
				cells[y][x].setState(State::End);
			}
			else if (g.isWall(x, y))
			{
				cells[y][x].setState(State::Wall);
			}
			else
			{
				cells[y][x].setState(State::Empty);
			}
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}

		window.clear(sf::Color::Black);
		for (int y = 0; y < g.HEIGHT; y++)
		{
			for (int x = 0; x < g.WIDTH; x++)
			{
				window.draw(cells[y][x].shape);
			}
		}

		window.display();
	}

	return 0;
}