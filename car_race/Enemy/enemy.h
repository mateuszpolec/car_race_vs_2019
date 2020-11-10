#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"

class Enemy {

	sf::Sprite enemy;
	sf::Texture enemyTexture;
	

public:

	sf::Sprite getEnemySpriteObject();
	
	void moveToStart();

	void checkPossibleMove();

};

#endif