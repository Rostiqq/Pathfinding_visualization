#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Grid.h"
#include "Cell.h"
#include "App.h"

App::App(int width, int height) : grid(height, width)
{
    grid.generateGrid();

    window.create(sf::VideoMode(600, 600), "Pathfinding");
    start = {0, 0};
    end = {grid.WIDTH - 1, grid.HEIGHT - 1};

    visited.resize(grid.HEIGHT * grid.WIDTH, false);
    parent.resize(grid.HEIGHT * grid.WIDTH, {-1, -1});
    cells.resize(height, std::vector<Cell>(grid.WIDTH));

    float sizeX = 800.0f / grid.WIDTH;
    float sizeY = 600.0f / grid.HEIGHT;
    cellSize = std::min(sizeX, sizeY);

    for (int y = 0; y < grid.HEIGHT; y++)
    {
        for (int x = 0; x < grid.WIDTH; x++)
        {
            cells[y][x].shape.setPosition(x * cellSize, y * cellSize);
            cells[y][x].shape.setSize(sf::Vector2f(cellSize, cellSize));

            if (y == start.y && x == start.x)
            {
                cells[y][x].setState(State::Start);
            }
            else if (y == end.y && x == end.x)
            {
                cells[y][x].setState(State::End);
            }
            else if (grid.isWall(x, y))
            {
                cells[y][x].setState(State::Wall);
            }
            else
            {
                cells[y][x].setState(State::Empty);
            }
        }
    }
}

void App::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                int cellX = mouseX / cellSize;
                int cellY = mouseY / cellSize;

                if (cellX >= 0 && cellX < grid.WIDTH &&
                    cellY >= 0 && cellY < grid.HEIGHT)
                {
                    if (!isStartOrEnd({cellX, cellY}))
                    {
                        running = false;
                        reset();
                        running = true;
                        startASTAR();
                        
                        if (cells[cellY][cellX].state == State::Wall)
                        {
                            cells[cellY][cellX].setState(State::Empty);
                            grid.changeGridStatus(cellX, cellY);
                        }
                        else
                        {
                            cells[cellY][cellX].setState(State::Wall);
                            grid.changeGridStatus(cellX, cellY);
                        }
                    }
                }
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Num1)
            {
                reset();
                currentAlgo = Algorithm::BFS;
                running = true;
                startBFS();
            }

            if (event.key.code == sf::Keyboard::Num2)
            {
                reset();
                currentAlgo = Algorithm::DFS;
                running = true;
                startDFS();
            }

            if (event.key.code == sf::Keyboard::Num3)
            {
                reset();
                currentAlgo = Algorithm::ASTAR;
                running = true;
                startASTAR();
            }
        }
    }
}

void App::render()
{
    window.clear();

    for (int y = 0; y < grid.HEIGHT; y++)
    {
        for (int x = 0; x < grid.WIDTH; x++)
        {
            window.draw(cells[y][x].shape);
        }
    }

    window.display();
}

void App::update()
{
    switch (currentAlgo)
    {
    case Algorithm::ASTAR:
        updateAStar();
        break;
    case Algorithm::BFS:
        updateBFS();
        break;
    case Algorithm::DFS:
        updateDFS();
        break;
    }
}

void App::updateBFS()
{
    if (!running)
        return;

    if (clock.getElapsedTime().asSeconds() < delay)
        return;

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
        if (current.x == grid.WIDTH - 1 && current.y == grid.HEIGHT - 1)
        {
            running = false;

            // Vykresliť cestu
            end = current;
            while (!(end.x == start.x && end.y == start.y))
            {
                cells[end.y][end.x].setState(State::Path);
                int index = end.y * grid.WIDTH + end.x;
                end = parent[index];
            }
            cells[start.y][start.x].setState(State::Start);
            cells[grid.WIDTH - 1][grid.HEIGHT - 1].setState(State::End);
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
            int count = grid.getNeighbour(neighbours, current);

            for (int i = 0; i < count; i++)
            {
                Node nb = neighbours[i];
                int nbIndex = nb.y * grid.WIDTH + nb.x;

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

void App::updateDFS()
{
    if (!running)
        return;

    if (clock.getElapsedTime().asSeconds() < delay)
        return;

    clock.restart();

    if (!s.empty())
    {
        // Označiť posledný uzol ako navštívený
        if (last.x != -1 && !isStartOrEnd(last))
        {
            cells[last.y][last.x].setState(State::Visited);
        }

        Node current = s.top();
        s.pop();

        // Skontrolovať či sme našli cieľ
        if (current.x == grid.WIDTH - 1 && current.y == grid.HEIGHT - 1)
        {
            running = false;

            // Vykresliť cestu
            end = current;
            while (!(end.x == start.x && end.y == start.y))
            {
                cells[end.y][end.x].setState(State::Path);
                int index = end.y * grid.WIDTH + end.x;
                end = parent[index];
            }
            cells[start.y][start.x].setState(State::Start);
            cells[grid.WIDTH - 1][grid.HEIGHT - 1].setState(State::End);
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
            int count = grid.getNeighbour(neighbours, current);

            for (int i = 0; i < count; i++)
            {
                Node nb = neighbours[i];
                int nbIndex = nb.y * grid.WIDTH + nb.x;

                if (!visited[nbIndex])
                {
                    visited[nbIndex] = true;
                    parent[nbIndex] = current;
                    s.push(nb);
                }
            }

            last = current;
        }
    }
}

void App::updateAStar()
{
    if (!running)
        return;
    if (clock.getElapsedTime().asSeconds() < delay)
        return;
    clock.restart();

    if (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();
        int currentIndex = current.y * grid.WIDTH + current.x;

        if (visited[currentIndex])
            return;

        visited[currentIndex] = true;

        if (last.x != -1 && !isStartOrEnd(last))
        {
            cells[last.y][last.x].setState(State::Visited);
        }

        if (!isStartOrEnd(current))
        {
            cells[current.y][current.x].setState(State::Visiting);
        }

        if (current.x == end.x && current.y == end.y)
        {
            running = false;
            end = current;

            while (!(end.x == start.x && end.y == start.y))
            {
                cells[end.y][end.x].setState(State::Path);
                int index = end.y * grid.WIDTH + end.x;
                end = parent[index];
            }
            cells[start.y][start.x].setState(State::Start);
            cells[grid.WIDTH - 1][grid.HEIGHT - 1].setState(State::End);
            return;
        }

        Node neighbours[4];
        int count = grid.getNeighbour(neighbours, current);

        for (int i = 0; i < count; i++)
        {
            Node nb = neighbours[i];
            int nbIndex = nb.y * grid.WIDTH + nb.x;

            if (!visited[nbIndex])
            {
                float newG = gCostList[currentIndex] + 1;

                if (newG < gCostList[nbIndex])
                {
                    gCostList[nbIndex] = newG;
                    nb.gCost = newG;
                    nb.hCost = float(abs(nb.x - end.x) + abs(nb.y - end.y));
                    nb.fCost = nb.gCost + nb.hCost;

                    parent[nbIndex] = current;
                    pq.push(nb);
                }
            }
        }

        last = current;
    }
}

void App::run()
{
    while (window.isOpen())
    {
        handleInput();
        update();
        render();
    }
}