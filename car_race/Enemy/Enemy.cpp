#include "enemy.h"

sf::Sprite Enemy::getEnemySpriteObject() {
	this->enemyTexture.loadFromFile("./Assets/car_sprite_3.png");
	enemy.setTexture(this->enemyTexture);
	enemy.setScale(3.0, 3.0);
	enemy.setOrigin(4.5f, 7.0f);
	return enemy;
}

void Enemy::checkPossibleMove() {
	std::cout << "Checking possible move";
}

void Enemy::moveToStart() {
	int xPosition = rand() % 175 + 175;
	int yPosition = rand() % 200 + 575;
	this->enemy.rotate(180.f);
	this->enemy.setPosition(xPosition, yPosition);
}

