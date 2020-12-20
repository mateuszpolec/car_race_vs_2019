#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"
#include <cmath>
#include <set>

class Enemy {

public:
	short actualPointToGo = 0;
	int currentLap = 0;
	float timeCounter = 0;
	int totalPointsCompleted = 0;

private:
	sf::Sprite m_Enemy;
	sf::Texture enemyTexture;
	sf::Clock clock;
	sf::Vector2f movementVector;
	sf::Vector2f forwardVector = { 0.f, 1.f };

	// Section for Movement
	int halfOfPlot = 0;
	bool tooFar = false;

	// Section for lap measurment
	bool isNextLap = false;
	std::set<int> checkpointsReached = {};


	struct nextRandomBezierPoint {

		int x, y;

		nextRandomBezierPoint(int random_x, int random_y) : x(random_x), y(random_y) {}
	};

	// State of textures - used for getting sprite object
	bool textureIsLoaded = false;
	

public:

	float currentSpeed = 0;

	std::string m_Name;

	Enemy(std::string name);

	~Enemy();

	std::vector <sf::Vector2f> pointsToFollow = {};

	/**
	* getEnemySpriteObject
	* Function sets and returns the sprite(texture) of enemy
	* @return SFML Sprite Object - enemy scaled sprite with texture
	*/
	sf::Sprite getEnemySpriteObject();
	
	/**
	* moveToStart
	* Function moves enemy to start positon at beggining
	*/
	void moveToStart();
	

	/**
	* moveEnemy
	* Function that changes the cartesian system to polar system and then the enemy
	* spirite is going to follow the nearest point. 
	* More in .cpp file
	*/
	void moveEnemy();


	/**
	* createTrack
	* Function that creates the track to follow by enemy.
	* More in .cpp file
	*/
	void createTrack();


	/**
	* checkEnemyCollision
	* Check what tile is under enemy
	* @param tileID std::uint32_t Tile ID of what's under the Enemy Sprite
	*/
	void checkEnemyCollision(std::uint32_t tileID);

	//TODO: Documentation
	void checkCollisionInBezier();

	/**
	* setPointsToFollow
	* Sets points to follow for enemy sprite
	* @param std::vector with points to follow in it
	*/
	void setPointsToFollow(std::vector<sf::Vector2f> pointsToFollowForEnemy);

	/**
	* getEnemyPositionX
	* Function that returns enemy position in X axis including size of tile
	* @return ABS int value with enemy position in X axis
	*/
	int getEnemyPositionX();

	/**
	* getEnemyPositionY
	* Function that returns enemy position in Y axis including size of tile
	* @return ABS int value with enemy position in Y axis
	*/
	int getEnemyPositionY();

	/**
	* showName
	* Function that display enemy name on the map just a little above enemy sprite sprite
	* @param sf::Font gameFont - Reference to font variable
	* @return sf::Text text - Player name with font, size, and all needed attributes
	*/
	sf::Text showName(sf::Font& gameFont);


};

#endif