#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"

class Enemy {

	sf::Sprite enemy;
	sf::Texture enemyTexture;


	// State of textures - used for getting sprite object
	bool textureIsLoaded = false;
	

public:

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
	
	void checkSurronding();

	void checkPossibleMove();

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