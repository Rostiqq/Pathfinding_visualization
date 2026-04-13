#include <iostream>
#include <vector>
#include <queue>
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
	std::queue<Node> q;
	std::vector<bool> visited;
	std::vector<Node> parent;
	bool running = false;
	sf::Clock clock;
	float delay = 0.01f;

	std::cout << "Size of grid: ";
	std::cin >> columns >> rows;

	Grid g(columns, rows);
	g.generateGrid();

	float cellSizeX = windowWidth / float(columns);
	float cellSizeY = windowHeight / float(rows);
	float cellSize = std::min(cellSizeX, cellSizeY);

	window.create(sf::VideoMode(columns * cellSize, rows * cellSize), "PATH", sf::Style::Default);
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
	auto pathBFS = p.bfs(g, n);
	std::vector<std::vector<Cell>> cells;
	cells.resize(g.HEIGHT, std::vector<Cell>(g.WIDTH));
	bool showPath = false;

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

				if (event.key.code == sf::Keyboard::Space)
				{
					running = true;

					visited.assign(g.WIDTH * g.HEIGHT, false);
					parent.resize(g.WIDTH * g.HEIGHT);

					while (!q.empty()) q.pop();
					
					q.push(n);
					int index = n.y * g.WIDTH + n.x;
					visited[index] = true;
					showPath = false;
					break;
				}
			}
		}

		if (running)
		{
			if (clock.getElapsedTime().asSeconds() >= delay)
			{
				clock.restart();
				if (!q.empty())
				{
					Node current = q.front();
					q.pop();

					if (current.x == g.WIDTH - 1 && current.y == g.HEIGHT - 1)
					{
						running = false;

						Node end = current;

						while (!(end.x == n.x && end.y == n.y))
						{
							cells[end.y][end.x].setState(State::Path);
							int index = end.y * g.WIDTH + end.x;
							end = parent[index];
						}
					}

					if (!(current.x == 0 && current.y == 0) &&
						!(current.x == g.WIDTH - 1 && current.y == g.HEIGHT - 1))
					{
						cells[current.y][current.x].setState(State::Visiting);
					}

					Node neighbours[4];
					int couunt = g.getNeighbour(neighbours, current);

					for (int i = 0; i < couunt; i++)
					{
						Node nb = neighbours[i];
						int nbIndex = nb.y * g.WIDTH + nb.x;
						if (!visited[nbIndex])
						{
							visited[nbIndex] = true;
							parent[nbIndex] = current;
							q.push(nb);
						}
					}
				}
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
}