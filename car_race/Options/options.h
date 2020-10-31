#include <SFML/Graphics.hpp>

class Options {
	
	public:

		// Static variables and options
		float playerMaxVelocity = 300.f;
		float playerMaxAcceleration = 150.f;
		float playerMaxDeceleration = 150.f;
		float playerFrictionForce = 60.f;
		float playerRotateAmmount = 180.f;

		/**
		* mathDotProductCalcualtion
		* Function that counts the product of two vectors
		* @param SFML Object Vector2f - First one to count
		* @param SFML Object Vector2f - Second one to count
		* @return float - Scalar product of two vectors
		*/
		float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv);

};