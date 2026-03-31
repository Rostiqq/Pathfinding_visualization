#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include "Pathfinding.h"
#include "Grid.h"
#include "Node.h"

std::vector<Node> Pathfinding::bfs(Grid &grid, Node &node)
{
    std::queue<Node> q;
    std::vector<bool> visited;
    std::vector<Node> parent;

    visited.resize(grid.HEIGHT * grid.WIDTH, false);
    parent.resize(grid.HEIGHT * grid.WIDTH);

    q.push(node);
    int index = node.y * grid.WIDTH + node.x;
    visited[index] = true;

    bool found = false;
    Node end;
    while (!q.empty())
    {
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

        std::vector<Node> path;
        while (!(end.x == node.x && end.y == node.y))
        {
            path.push_back(end);
            int index = end.y * grid.WIDTH + end.x;
            end = parent[index];
        }
        path.push_back(node);
        std::reverse(path.begin(), path.end());

        return path;
    }
    return {};
}

void Pathfinding::drawPath(Grid &grid, std::vector<Node> &path, Node &start)
{
    for (int y = 0; y < grid.HEIGHT; y++)
    {
        for (int x = 0; x < grid.WIDTH; x++)
        {
            bool inPath = false;
            for (const Node &p : path)
            {
                if (p.y == y && p.x == x)
                {
                    inPath = true;
                    break;
                }
            }

            if (x == start.x && y == start.y)
            {
                std::cout << "S ";
            }
            else if (x == grid.WIDTH - 1 && y == grid.HEIGHT - 1)
            {
                std::cout << "E ";
            }
            else if (inPath)
            {
                std::cout << "+ ";
            }
            else if (grid.isWall(x, y))
            {
                std::cout << "| ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    if (path.size() == 0)
    {
        std::cout << "Path not found\n";
    }
    else
    {
        std::cout << "Length of path: " << path.size() << "\n";
    }
}

std::vector<Node> Pathfinding::dfs(Grid &grid, Node &node)
{
    std::stack<Node> s;
    std::vector<bool> visited;
    std::vector<Node> parent;

    visited.resize(grid.HEIGHT * grid.WIDTH, false);
    parent.resize(grid.HEIGHT * grid.WIDTH);

    s.push(node);
    int index = node.y * grid.WIDTH + node.x;
    visited[index] = true;

    bool found = false;
    Node end;
    while (!s.empty())
    {
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

        std::vector<Node> path;
        while (!(end.x == node.x && end.y == node.y))
        {
            path.push_back(end);
            int index = end.y * grid.WIDTH + end.x;
            end = parent[index];
        }
        path.push_back(node);
        std::reverse(path.begin(), path.end());

        return path;
    }
    return {};
}

std::vector<Node> reconstructPath(Node start, Node end, const std::vector<Node>& parent, int width) {
    std::vector<Node> path;
    Node current = end;
    while (!(current.x == start.x && current.y == start.y)) {
        path.push_back(current);
        int index = current.y * width + current.x;
        current = parent[index];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}