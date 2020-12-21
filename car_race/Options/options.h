#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../FileWorker/RouteCreator.h"


// Variables for handling screen size & tile size
const static inline int s_screenHeight = 1200;
const static inline int s_screenWidth = 800;
const static inline int s_tileSize = 12;

// Variables for movement
static inline float s_maxVelocity = 250.f;
static inline float s_maxAcceleration = 125.f;
static inline float s_maxDeceleration = 125.f;
static inline float s_frictionForce = 60.f;
static inline float s_rotateAmmount = 180.f;
static inline float s_Grass_frictionForce = 100.f;

// Variables for ID of static blocks on map
const static int s_GrassTileID = 1;
const static int s_checkpointOneTleID = 28382;
const static int s_checkpointTwoTileID = 28383;
const static int s_checkpointThreeTileID = 28384;
const static int s_StartblockTileID = 28385;
const static int s_BezierBlockPointID = 28386;

const std::vector<sf::Vector2f> startingPlacesPoints = {
	sf::Vector2f { 485, 1275 },
	sf::Vector2f { 570, 1315 },
	sf::Vector2f { 485, 1355 },
	sf::Vector2f { 570, 1395 },
	sf::Vector2f { 485, 1435 },
	sf::Vector2f { 570, 1475 },
	sf::Vector2f { 485, 1515 },
	sf::Vector2f { 570, 1555 },
	sf::Vector2f { 485, 1595 },
	sf::Vector2f { 570, 1645 }
};

// vector of paths  to all avaiable textures

const static inline std::vector<std::string> pathsToTextures = {
	"./Assets/car_sprite_1.png",
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
float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv);

/**
* randomValueFromScope
* Function that returns random value from given start number and scope
* Example: For given int start = 1, and scope = 10 the result will be random integer from <1; 10>
* @param int start - Minimum number that you want to have in random scope
* @param int scope - How big is scope for random value
* @return - random int from given start point and scope
*/
static int randomValueFromScope(int start, int scope);


/**
* isThereAnyDuplicates
* Check if there's any duplicate value in given vector
* @param std::vector with integers
* @return boolean, if there's an duplicate value the return will be True, if not - False
*/
bool isThereAnyDuplicates(std::vector<int>& pointsToSort);

/**
* removeDuplicatesFromVector
* Change the value of duplicate value from value to next nearest number.
* Example: For given vector with numbers 442, 442 the result will be 443, 442
* @param Reference to std::vector with numbers
*/
void removeDuplicatesFromVector(std::vector<int>& pointsToSort);

#endif