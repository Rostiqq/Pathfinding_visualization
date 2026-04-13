#pragma once
#include <SFML/Graphics.hpp>

enum class State
{
    Empty,
    Wall,
    Start,
    End,
    Path,
    Visiting
};

class Cell
{
public:
    sf::RectangleShape shape;
    State state = State::Empty;

    void setState(State s);
};
