#include "options.h"

float Options::mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv) {
	return lv.x * rv.x + lv.y * rv.y;
}