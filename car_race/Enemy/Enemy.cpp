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

void Enemy::checkSurronding(std::vector<int> leftSideTiles, std::vector<int> upSideTiles, std::vector<int> rightSideTiles) {

	short multiplierForLeftSide = count(leftSideTiles.begin(), leftSideTiles.end(), Options::GrassTileID);
	short multiplierForUpSide = count(upSideTiles.begin(), upSideTiles.end(), Options::GrassTileID);
	short multiplierForRightSide = count(rightSideTiles.begin(), rightSideTiles.end(), Options::GrassTileID);

	float deltaTime = this->clock.restart().asSeconds();

	if(multiplierForUpSide == 0) {
		this->currentSpeedY -= 10 * deltaTime;
	}


	this->mVector.y = this->currentSpeedY;
	for (int up : upSideTiles) {
		std::cout << up << " ";
	}
}

void Enemy::moveEnemy() {
	sf::Vector2f oldPosition = this->enemy.getPosition();
	sf::Vector2f newPosition = oldPosition + mVector;
	this->enemy.setPosition(newPosition);
	//sf::Vector2f oldVector = this->movmentVector;
	//sf::Transform transform;

	//transform.rotate(this->enemy.getRotation());
	//this->movmentVector = transform.transformPoint(this->forwardVector);

	//this->currentSpeed *= Options::mathDotProductCalculation(oldVector, this->movmentVector);

	//this->enemy.move(this->movmentVector * this->currentSpeed * 0.05f);
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
