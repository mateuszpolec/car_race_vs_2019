#include "options.h"

float Options::mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv) {
	return lv.x * rv.x + lv.y * rv.y;
}

void Options::setVelocityAndAccelerationForGrass() {
	Options::playerMaxAcceleration = 25.f;
	Options::playerMaxVelocity = 25.f;
}

void Options::setVelocityAndAccelerationForAsphalt() {
	Options::playerMaxAcceleration = 125.f;
	Options::playerMaxVelocity = 300.f;
}