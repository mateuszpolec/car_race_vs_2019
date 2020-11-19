#include "RouteCreator.h"

std::vector<sf::Vector2f> CalcCubicBezier(
    const sf::Vector2f& start,
    const sf::Vector2f& end,
    const sf::Vector2f& startControl,
    const sf::Vector2f& endControl,
    const size_t numSegments)
{
    std::vector<sf::Vector2f> ret;
    if (!numSegments) // Any points at all?
        return ret;

    ret.push_back(start); // First point is fixed
    float p = 1.f / numSegments;
    float q = p;
    for (size_t i = 1; i < numSegments; i++, p += q) // Generate all between
        ret.push_back(p * p * p * (end + 3.f * (startControl - endControl) - start) +
            3.f * p * p * (start - 2.f * startControl + endControl) +
            3.f * p * (startControl - start) + start);
    ret.push_back(end); // Last point is fixed
    return ret;
}