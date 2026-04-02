#pragma once
class Node
{
public:
	int x;
	int y;
	bool wall;
	float gCost;
	float hCost;
	float fCost;

	bool hasParent = false;
};