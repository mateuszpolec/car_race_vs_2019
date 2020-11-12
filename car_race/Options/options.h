#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Options {
	
	public:

		// Variables for movement
		static inline float maxVelocity = 300.f;
		static inline float maxAcceleration = 125.f;
		static inline float maxDeceleration = 125.f;
		static inline float frictionForce = 60.f;
		static inline float rotateAmmount = 180.f;

		// Variables for ID of static blocks on map

		const float grassFrictionForce = 100.f;
		const static int GrassTileID = 28381;
		const static int checkpointOneTleID = 28383;
		const static int checkpointTwoTileID = 28384;
		const static int checkpointThreeTileID = 28385;
		const static int StartblockTileID = 28386;

		// vector of paths  to all avaiable textures

		const static inline std::vector<std::string> pathsToTextures = {
			"./Assets/car_sprite_1.png"
			"./Assets/car_sprite_2.png",
			"./Assets/car_sprite_3.png",
			"./Assets/car_sprite_4.png",
			"./Assets/car_sprite_5.png",
			"./Assets/car_sprite_6.png",
			"./Assets/car_sprite_7.png",
			"./Assets/car_sprite_8.png"
		};


		/**
		* mathDotProductCalcualtion
		* Function that counts the product of two vectors
		* @param SFML Object Vector2f - First one to count
		* @param SFML Object Vector2f - Second one to count
		* @return float - Scalar product of two vectors
		*/
		static float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv);

		/**
		* TODO: Create documentation
		*/
		void setVelocityAndAccelerationForGrass();

		/**
		* TODO: Create documentation
		*/
		void setVelocityAndAccelerationForAsphalt();

};

#endif