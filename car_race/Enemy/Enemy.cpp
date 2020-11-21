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


void Enemy::moveToStart() {
	int xPosition = rand() % 175 + 175;
	int yPosition = rand() % 200 + 575;
	this->enemy.rotate(180.f);
	this->enemy.setPosition(xPosition, yPosition);
}

void Enemy::moveEnemy() {
	float deltaTime = this->clock.restart().asSeconds();
	sf::Vector2f pointToGo = this->pointsToFollow[this->actualPointToGo];
	sf::Vector2f oldPosition = this->enemy.getPosition();

	this->currentSpeed = 15;

	float r = sqrt(pow((pointToGo.x - oldPosition.x), 2) + pow((pointToGo.y - oldPosition.y), 2));
	float x = pointToGo.x - oldPosition.x;
	float y = pointToGo.y - oldPosition.y;
	float angle_sin = asin(x / r) * 180.0 / 3.14;
	float angle_cos = acos(y / r) * 180.0 / 3.14;

	if (angle_sin < 90 && this->halfOfPlot == 0) {
		this->enemy.setRotation(180 + angle_sin);
	}

	if (this->actualPointToGo == 24) {
		this->halfOfPlot = 1;
	}

	if (this->halfOfPlot == 1) {
		this->enemy.setRotation(360 - angle_sin);
	}

	if (this->actualPointToGo == 82) {
		this->halfOfPlot = 0;
	}



	sf::Vector2f oldVector = this->movementVector;
	sf::Transform transform;

	transform.rotate(this->enemy.getRotation());
	this->movementVector = transform.transformPoint(this->forwardVector);

	//this->currentSpeed *= Options::mathDotProductCalculation(oldVector, this->movementVector);

	this->enemy.move(this->movementVector * this->currentSpeed);

	std::cout << r << "\n";

	if (r < 100) {
		this->actualPointToGo++;
		if (this->actualPointToGo > 98) {
			this->actualPointToGo = 0;
		}
	}

}
void Enemy::setPointsToFollow(std::vector < sf::Vector2f > pointsToFollowForEnemy) {
	this->pointsToFollow = pointsToFollowForEnemy;

}


double Enemy::checkPossibleMove() {
	return 0;
}




int Enemy::getEnemyPositionX() {
	return std::abs((int) this->enemy.getPosition().x / 12);
}

int Enemy::getEnemyPositionY() {
	return std::abs((int)this->enemy.getPosition().y / 12);
}
