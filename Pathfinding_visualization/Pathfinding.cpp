#include <iostream>
#include <algorithm>
#include <queue>
#include "Pathfinding.h"
#include "Grid.h"
#include "Node.h"

std::vector<Node> Pathfinding::bfs(Grid& grid, Node& node)
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
 
        std::cout << "BFS finished, path size: " << path.size() << "\n";
        return path;
 
    }
    return {};
}