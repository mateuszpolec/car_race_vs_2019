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

const sf::Vector2f firstPlaceStartingPoint = { 485, 1275 };
const sf::Vector2f secondPlaceStartingPoint = { 570, 1315 };
const sf::Vector2f thirdPlaceStartingPoint = { 485, 1355 };
const sf::Vector2f fourthPlaceStartingPoint = { 570, 1395 };
const sf::Vector2f fifthPlaceStartingPoint = { 485, 1435 };
const sf::Vector2f sixthPlaceStartingPoint = { 570, 1475 };
const sf::Vector2f seventhPlaceStartingPoint = { 485, 1515 };
const sf::Vector2f eightPlaceStartingPoint = { 570, 1555 };
const sf::Vector2f ninthPlaceStartingPoint = { 485, 1595 };
const sf::Vector2f tenPlaceStartingPoint = { 570, 1645 };
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
* TODO: Create documentation
*/
void setVelocityAndAccelerationForGrass();

/**
* TODO: Create documentation
*/
void setVelocityAndAccelerationForAsphalt();

/**
* TODO: Create documentation
*/
static int randomValueFromScope(int start, int scope);

/**
* TODO: Create documentation	
*/
void loadFont();

#endif