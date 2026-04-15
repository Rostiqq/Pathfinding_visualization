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
	int windowHeight = 600;
	int windowWidth = 800;
	int columns, rows;

	Pathfinding p;
	Node n{0, 0};
	Node last = {-1, -1};
	Node end;

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

	float cellSize = std::min(windowWidth / float(columns), windowHeight / float(rows));

	window.create(sf::VideoMode(columns * cellSize, rows * cellSize), "PATH", sf::Style::Default);

	std::vector<std::vector<Cell>> cells;
	cells.resize(g.HEIGHT, std::vector<Cell>(g.WIDTH));

	// Lambda na kontrolu či je uzol start alebo end
	auto isStartOrEnd = [&](Node node)
	{
		return (node.x == 0 && node.y == 0) ||
			   (node.x == g.WIDTH - 1 && node.y == g.HEIGHT - 1);
	};

	// Inicializácia buniek
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

	// Main loop
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
					parent.assign(g.WIDTH * g.HEIGHT, {-1, -1});

					while (!q.empty())
						q.pop();

					q.push(n);
					visited[n.y * g.WIDTH + n.x] = true;
					break;
				}
			case sf::Event::MouseButtonPressed:
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				int gridX = mousePos.x / cellSize;
				int gridY = mousePos.y / cellSize;

				if (gridX >= 0 && gridX < g.WIDTH && gridY >= 0 && gridY < g.HEIGHT)
				{
					if (!(gridX == 0 && gridY == 0) && !(gridX == g.WIDTH - 1 && gridY == g.HEIGHT - 1))
					{
						bool isWallNow = g.changeGridStatus(gridX, gridY);
						if (isWallNow)
							cells[gridY][gridX].setState(State::Wall);
						else
							cells[gridY][gridX].setState(State::Empty);
					}
				}
			}
		}

		// BFS animácia
		if (running && clock.getElapsedTime().asSeconds() >= delay)
		{
			clock.restart();

			if (!q.empty())
			{
				// Označiť posledný uzol ako navštívený
				if (last.x != -1 && !isStartOrEnd(last))
				{
					cells[last.y][last.x].setState(State::Visited);
				}

				Node current = q.front();
				q.pop();

				// Skontrolovať či sme našli cieľ
				if (current.x == g.WIDTH - 1 && current.y == g.HEIGHT - 1)
				{
					running = false;

					// Vykresliť cestu
					end = current;
					while (!(end.x == n.x && end.y == n.y))
					{
						cells[end.y][end.x].setState(State::Path);
						int index = end.y * g.WIDTH + end.x;
						end = parent[index];
					}
					cells[n.y][n.x].setState(State::Start);
					cells[g.WIDTH - 1][g.HEIGHT - 1].setState(State::End);
				}
				else
				{
					// Označiť aktuálny uzol ako navštevovaný
					if (!isStartOrEnd(current))
					{
						cells[current.y][current.x].setState(State::Visiting);
					}

					// Spracovať susedov
					Node neighbours[4];
					int count = g.getNeighbour(neighbours, current);

					for (int i = 0; i < count; i++)
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

					last = current;
				}
			}
		}

		// Rendering
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