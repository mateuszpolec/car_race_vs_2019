#include <SFML/Graphics.hpp>

class Options {
	
	public:

		// Static variables and options
		float playerMaxVelocity = 300.f;
		float playerMaxAcceleration = 150.f;
		float playerMaxDeceleration = 150.f;
		float playerRotateAmmount = 180.f;

		// Methods
		float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv);

};