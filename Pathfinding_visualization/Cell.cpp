#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cell.h"

void Cell::setState(State s)
{
    state = s;
    if (state == State::Empty)
    {
        shape.setFillColor(sf::Color(20, 20, 20));
    }
    else if (state == State::Wall)
    {
        shape.setFillColor(sf::Color(10, 10, 10));
    }
    else if (state == State::Start)
    {
        shape.setFillColor(sf::Color::Blue);
    }
    else if (state == State::End)
    {
        shape.setFillColor(sf::Color::Blue);
    }
    else if (state == State::Path)
    {
        shape.setFillColor(sf::Color::White);
    }
    else if (state == State::Visiting)
    {
        shape.setFillColor(sf::Color::Yellow);
    }
    else if (state == State::Visited)
    {
        shape.setFillColor(sf::Color(0, 145, 255)); 
    }
}
