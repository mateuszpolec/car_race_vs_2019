#ifndef ROUTE_CREATOR_H
#define ROUTE_CREATOR_H

#include <SFML/Graphics.hpp>

std::vector<sf::Vector2f> CalcCubicBezier(
    const sf::Vector2f& start,
    const sf::Vector2f& end,
    const sf::Vector2f& startControl,
    const sf::Vector2f& endControl,
    const size_t numSegments);

#endif