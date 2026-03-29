#pragma once
#include "Grid.h"
#include "Node.h"

class Pathfinding
{
public:
	std::vector<Node> bfs(Grid &grid, Node &node);
	std::vector<Node> dfs(Grid &grid, Node &node);
	void drawPath(Grid &grid, std::vector<Node> &path, Node &Node);
};
