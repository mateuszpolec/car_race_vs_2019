#include "options.h"

float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv) {
	return lv.x * rv.x + lv.y * rv.y;
}

void setVelocityAndAccelerationForGrass() {
	s_maxAcceleration = 25.f;
	s_maxVelocity = 25.f;
}

void setVelocityAndAccelerationForAsphalt() {
	s_maxAcceleration = 125.f;
	s_maxVelocity = 300.f;
}

int randomValueFromScope(int start, int scope) {
	return rand() % scope + start;
}
