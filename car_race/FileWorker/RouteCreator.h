#ifndef ROUTE_CREATOR_H
#define ROUTE_CREATOR_H

#include <SFML/Graphics.hpp>

/**
* 
* Function CalcCubicBezier
* Function that calculates the bezier curvature for given initial conditions
* 
* @param start sf::Vector2f - SFML Vector object for starting point for bezier curve
* @param end sf::Vector2f - SFML Vector object for ending point for bezier curve
* @param startControl sf::Vector2f - SFML Vector object, point in cartesian system for initial curvature
* @param endControl sf::Vector2f - SFML Vector object, point in cartesian system for final curvature
* @param numSegments size_t - size_t object for number of points in bezier Curve
* 
* @return Standard libary vector with SFML Vectors in int that represents the next points of Bezier Curve
*/
std::vector<sf::Vector2f> CalcCubicBezier(
    const sf::Vector2f& start,
    const sf::Vector2f& end,
    const sf::Vector2f& startControl,
    const sf::Vector2f& endControl,
    const size_t numSegments);

#endif