#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"
#include <cmath>

class Enemy {

	sf::Sprite enemy;
	sf::Texture enemyTexture;
	sf::Clock clock;
	sf::Vector2f movementVector;
	sf::Vector2f forwardVector = { 0.f, 1.f };

	short actualPointToGo = 0;
	float currentSpeed = 0;

	int halfOfPlot = 0;
	bool tooFar = false;

	// State of textures - used for getting sprite object
	bool textureIsLoaded = false;
	

public:
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
	
	void moveEnemy();

	double checkPossibleMove();

	void createTrack();

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


};

#endif