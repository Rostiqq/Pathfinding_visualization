#pragma once
#include "Grid.h"
#include "Node.h"

class Pathfinding
{
public:
	struct Compare
	{
		bool operator()(Node a, Node b)
		{
			return a.fCost > b.fCost;
		}
	};

	std::vector<Node> bfs(Grid &grid, Node &node);
	std::vector<Node> dfs(Grid &grid, Node &node);
	std::vector<Node> Astar(Grid &grid, Node &node);

	void drawPath(Grid &grid, std::vector<Node> &path, Node &Node);
	std::vector<Node> reconstructPath(Node start, Node end, const std::vector<Node> &parent, int width);
};
