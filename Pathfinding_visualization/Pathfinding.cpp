#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <cfloat>
#include "Pathfinding.h"
#include "Grid.h"
#include "Node.h"

std::vector<Node> Pathfinding::bfs(Grid &grid, Node &node)
{
    std::queue<Node> q;
    std::vector<bool> visited;
    std::vector<Node> parent;
    int visitedCount = 0;
    visited.resize(grid.HEIGHT * grid.WIDTH, false);
    parent.resize(grid.HEIGHT * grid.WIDTH);
    Node start = node;
    q.push(node);
    int index = node.y * grid.WIDTH + node.x;
    visited[index] = true;

    bool found = false;
    Node end;
    while (!q.empty())
    {
        visitedCount++;
        Node current = q.front();

        q.pop();

        if (current.x == grid.WIDTH - 1 && current.y == grid.HEIGHT - 1)
        {
            end = current;
            found = true;
            break;
        }

        Node neighbors[4];
        int n = grid.getNeighbour(neighbors, current);
        for (int i = 0; i < n; i++)
        {
            Node nb = neighbors[i];
            int nbIndex = nb.y * grid.WIDTH + nb.x;
            if (!visited[nbIndex])
            {
                visited[nbIndex] = true;
                parent[nbIndex] = current;
                q.push(nb);
            }
        }
    }
    if (found)
    {
        std::cout << "BFS visited vertex: " << visitedCount << "\n";
        return reconstructPath(start, end, parent, grid.WIDTH);
    }
    return {};
}

void Pathfinding::drawPath(Grid &grid, std::vector<Node> &path, Node &start)
{
    if (path.size() == 0)
    {
        std::cout << "Path not found\n";
        return;
    }
    std::vector<std::vector<bool>> pathGrid(grid.HEIGHT, std::vector<bool>(grid.WIDTH, false));
    for (const Node &p : path)
        pathGrid[p.y][p.x] = true;

    for (int y = 0; y < grid.HEIGHT; y++)
    {
        for (int x = 0; x < grid.WIDTH; x++)
        {
            if (x == start.x && y == start.y)
                std::cout << "S ";
            else if (x == grid.WIDTH - 1 && y == grid.HEIGHT - 1)
                std::cout << "E ";
            else if (pathGrid[y][x])
                std::cout << "+ ";
            else if (grid.isWall(x, y))
                std::cout << "| ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

std::vector<Node> Pathfinding::reconstructPath(Node start, Node end, const std::vector<Node> &parent, int width)
{
    std::vector<Node> path;
    Node current = end;
    while (!(current.x == start.x && current.y == start.y))
    {
        path.push_back(current);
        int index = current.y * width + current.x;
        current = parent[index];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    std::cout << "Lenght of path: " << path.size() << "\n";
    return path;
}

std::vector<Node> Pathfinding::dfs(Grid &grid, Node &node)
{
    std::stack<Node> s;
    std::vector<bool> visited;
    std::vector<Node> parent;
    int visitedCount = 0;

    visited.resize(grid.HEIGHT * grid.WIDTH, false);
    parent.resize(grid.HEIGHT * grid.WIDTH);

    s.push(node);
    int index = node.y * grid.WIDTH + node.x;
    visited[index] = true;

    bool found = false;
    Node end;
    while (!s.empty())
    {
        visitedCount++;
        Node current = s.top();
        s.pop();

        if (current.x == grid.WIDTH - 1 && current.y == grid.HEIGHT - 1)
        {
            found = true;
            end = current;
            break;
        }

        Node neighbours[4];
        int n = grid.getNeighbour(neighbours, current);

        for (int i = 0; i < n; i++)
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
    }
    if (found)
    {
        std::cout << "DFS visited vertex: " << visitedCount << std::endl;
        return Pathfinding::reconstructPath(node, end, parent, grid.WIDTH);
    }
    return {};
}

std::vector<Node> Pathfinding::Astar(Grid &grid, Node &node)
{
    std::priority_queue<Node, std::vector<Node>, Compare> pq;

    Node start = node;
    Node end;
    Node foundEnd;
    end.x = grid.WIDTH - 1;
    end.y = grid.HEIGHT - 1;
    int visitedCount = 0;

    std::vector<float> gCost(grid.WIDTH * grid.HEIGHT, FLT_MAX);
    std::vector<Node> parent;
    parent.resize(grid.HEIGHT * grid.WIDTH, Node{-1, -1});

    int index = node.y * grid.WIDTH + node.x;

    gCost[index] = 0;
    node.gCost = 0;
    node.hCost = float((abs(node.x - end.x)) + abs(node.y - end.y));
    node.fCost = node.gCost + node.hCost;
    bool found = false;
    pq.push(node);
    while (!pq.empty())
    {
        visitedCount++;
        Node current = pq.top();
        pq.pop();

        int currentIndex = current.y * grid.WIDTH + current.x;

        if (current.gCost > gCost[currentIndex])
            continue;

        if (current.x == end.x && current.y == end.y)
        {
            found = true;
            foundEnd = current;
            break;
        }

        Node neighbours[4];
        int n = grid.getNeighbour(neighbours, current);
        for (int i = 0; i < n; i++)
        {
            Node nb = neighbours[i];
            int nbIndex = nb.y * grid.WIDTH + nb.x;

            float newG = current.gCost + 1;

            if (newG < gCost[nbIndex])
            {
                nb.gCost = newG;
                nb.hCost = float(abs(nb.x - end.x) + abs(nb.y - end.y));
                nb.fCost = nb.gCost + nb.hCost;

                gCost[nbIndex] = newG;
                parent[nbIndex] = current;
                pq.push(nb);
            }
        }
    }
    if (found)
    {
        std::cout << "A* visited vertex: " << visitedCount << std::endl;
        return reconstructPath(start, foundEnd, parent, grid.WIDTH);
    }
    return {};
}