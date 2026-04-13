#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cell.h"

void Cell::setState(State s)
{
    state = s;
    if (state == State::Empty)
    {
        shape.setFillColor(sf::Color::White);
    }
    else if (state == State::Wall)
    {
        shape.setFillColor(sf::Color::Black);
    }
    else if (state == State::Start)
    {
        shape.setFillColor(sf::Color::Green);
    }
    else if (state == State::End)
    {
        shape.setFillColor(sf::Color::Blue);
    }
    else if (state == State::Path)
    {
        shape.setFillColor(sf::Color::Green);
    }
    else if (state == State::Visiting)
    {
        shape.setFillColor(sf::Color::Cyan);
    };
}
