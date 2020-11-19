#include "enemy.h"
#include "../FileWorker/sfml_layer_loader.h"

sf::Sprite Enemy::getEnemySpriteObject() {
	if (this->textureIsLoaded == false) {
		this->textureIsLoaded = true;
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


void Enemy::moveEnemy() {
	sf::Vector2f oldVector = this->movementVector;
	sf::Transform transform;

	transform.rotate(this->enemy.getRotation());
	this->movementVector = transform.transformPoint(this->forwardVector);

	this->currentSpeed *= Options::mathDotProductCalculation(oldVector, this->movementVector);

	this->enemy.move(this->movementVector * this->currentSpeed * 0.05f);
}

void Enemy::checkPossibleMove() {}

void Enemy::moveToStart() {
	int xPosition = rand() % 175 + 175;
	int yPosition = rand() % 200 + 575;
	this->enemy.rotate(180.f);
	this->enemy.setPosition(xPosition, yPosition);
}

int Enemy::getEnemyPositionX() {
	return std::abs((int) this->enemy.getPosition().x / 12);
}

int Enemy::getEnemyPositionY() {
	return std::abs((int)this->enemy.getPosition().y / 12);
}
