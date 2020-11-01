#include <SFML/Graphics.hpp>
#include <iostream>

class Options {
	
	public:

		// Variables for player movement
		float playerMaxVelocity = 300.f;
		float playerMaxAcceleration = 125.f;
		float playerMaxDeceleration = 125.f;
		float playerFrictionForce = 60.f;
		float playerRotateAmmount = 180.f;

		// Variables for ID of static blocks on map

		const float grassFrictionForce = 100.f;
		const static int GrassTileID = 28381;

		/**
		* mathDotProductCalcualtion
		* Function that counts the product of two vectors
		* @param SFML Object Vector2f - First one to count
		* @param SFML Object Vector2f - Second one to count
		* @return float - Scalar product of two vectors
		*/
		float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv);

		void setVelocityAndAccelerationForGrass();

		void setVelocityAndAccelerationForAsphalt();

};