#pragma once
class Node
{
public:
	int x;
	int y;
	bool wall;
	float gCost = __FLT_MAX__;
	float hCost;
	float fCost;

	bool hasParent = false;

	 bool operator>(const Node& other) const {
        return fCost > other.fCost;  
    }

    bool operator<(const Node& other) const {
        return fCost < other.fCost;
    }

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};