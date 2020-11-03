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
		const static int checkpointOneTleID = 28383;
		const static int checkpointTwoTileID = 28384;
		const static int checkpointThreeTileID = 28385;
		const static int StartblockTileID = 28386;

		/**
		* mathDotProductCalcualtion
		* Function that counts the product of two vectors
		* @param SFML Object Vector2f - First one to count
		* @param SFML Object Vector2f - Second one to count
		* @return float - Scalar product of two vectors
		*/
		float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv);

		/**
		* TODO: Create documentation
		*/
		void setVelocityAndAccelerationForGrass();

		/**
		* TODO: Create documentation
		*/
		void setVelocityAndAccelerationForAsphalt();

};