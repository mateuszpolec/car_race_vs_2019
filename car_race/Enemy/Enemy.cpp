#include "enemy.h"

sf::Sprite Enemy::getEnemySpriteObject() {
	if (this->isLoaded == false) {
		this->isLoaded = true;
		short randInt = rand() % 7;
		this->enemyTexture.loadFromFile(Options::pathsToTextures[randInt]);
		enemy.setTexture(this->enemyTexture);
		enemy.setScale(3.0, 3.0);
		enemy.setOrigin(4.5f, 7.0f);
		return enemy;
	}
	else {
		return enemy;
	}
}

void Enemy::checkPossibleMove() {
	std::cout << Options::pathsToTextures.size() << std::endl;
}

void Enemy::moveToStart() {
	int xPosition = rand() % 175 + 175;
	int yPosition = rand() % 200 + 575;
	this->enemy.rotate(180.f);
	this->enemy.setPosition(xPosition, yPosition);
}

