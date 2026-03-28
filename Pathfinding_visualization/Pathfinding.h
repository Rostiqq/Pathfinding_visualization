#pragma once
#include "Grid.h"
#include "Node.h"

class Pathfinding
{
public:
	std::vector<Node> bfs(Grid& grid,Node& node);
};
