#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Grid.h"
#include "Node.h"

enum class Algorithm
{
    BFS,
    ASTAR,
    DFS
};

class App
{
private:
    void render();
    void handleInput();
    void update();

    void updateBFS();
    void updateDFS();
    void updateAStar();

    sf::RenderWindow window;

    std::vector<std::vector<Cell>> cells;
    Grid grid;
    Node n;
    Node start;
    Node end;
    Node last = {-1, -1};
    sf::Clock clock;
    float delay = 0.01f;

    std::queue<Node> q;
    std::stack<Node> s;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::vector<bool> visited;
    std::vector<Node> parent;
    std::vector<float> gCostList;
    float gCost;
    float hCost;
    float fCost;
    float cellSize;

    bool running = false;
    bool resetRequest = false;
    Algorithm currentAlgo = Algorithm::BFS;
    bool isStartOrEnd(Node node)
    {
        return (node.x == start.x && node.y == start.y) ||
               (node.x == end.x && node.y == end.y);
    }




    public:
    void run();
    App(int width, int height);
    void reset()
    {
        last = {-1, -1};
        gCostList.clear();
        gCostList.resize(grid.WIDTH * grid.HEIGHT, std::numeric_limits<float>::infinity());
        int startIndex = start.y * grid.WIDTH + start.x;
        gCostList[startIndex] = 0;

        for (int i = 0; i < visited.size(); i++)
        {
            visited[i] = false;
        }
        for (auto &p : parent)
        {
            p = {-1, -1};
        }

        while (!pq.empty())
        {
            pq.pop();
        }
        while (!q.empty())
        {
            q.pop();
        }
        while (!s.empty())
        {
            s.pop();
        }
    }
    void startDFS()
    {
        s.push(start);
        visited[start.y * grid.WIDTH + start.x] = true;
    };
    void startBFS()
    {
        q.push(start);
        visited[start.y * grid.WIDTH + start.x] = true;
    };
    void startASTAR()
    {
        start.gCost = 0;
        start.hCost = float((abs(start.x - end.x)) + abs(start.y - end.y));
        start.fCost = start.gCost + start.hCost;
        pq.push(start);
    };
};
