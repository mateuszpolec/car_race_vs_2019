#include "options.h"

float Options::mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv) {
	return lv.x * rv.x + lv.y * rv.y;
}

void Options::setVelocityAndAccelerationForGrass() {
	Options::s_maxAcceleration = 25.f;
	Options::s_maxVelocity = 25.f;
}

void Options::setVelocityAndAccelerationForAsphalt() {
	Options::s_maxAcceleration = 125.f;
	Options::s_maxVelocity = 300.f;
}

int Options::randomValueFromScope(int start, int scope) {
	return rand() % scope + start;
}
