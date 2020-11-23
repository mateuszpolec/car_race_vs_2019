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

	if (this->currentSpeed < Options::maxVelocity) {
		this->currentSpeed += Options::maxAcceleration * deltaTime;
	}
	
	float r = sqrt(pow((pointToGo.x - oldPosition.x), 2) + pow((pointToGo.y - oldPosition.y), 2));
	float x = pointToGo.x - oldPosition.x;
	float angle_sin = asin(x / r) * 180.0 / 3.14;

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


	this->enemy.move(this->movementVector * this->currentSpeed * 0.05f);

	if (r < 100) {
		this->actualPointToGo++;
		this->tooFar = false;
		if (this->actualPointToGo > 98) {
			this->actualPointToGo = 0;
		}
	}
	else if (r > 300) {
		if(this->tooFar == true) {
			this->actualPointToGo += 5;
		}
		this->tooFar = true;
		if (this->actualPointToGo > 98) {
			this->actualPointToGo = 0;
		}
	}

}
void Enemy::setPointsToFollow(std::vector < sf::Vector2f > pointsToFollowForEnemy) {
	this->pointsToFollow = pointsToFollowForEnemy;

}

void Enemy::createTrack() {
	sf::VertexArray vertices(sf::LinesStrip, 0);

	std::vector<std::vector<sf::Vector2f>> vectorOfPoints;
	// Calculate the points on the curve (10 segments)

	std::vector<int> fp_Start = { rand() % 100 + 250, rand() % 25 + 575 };
	std::vector<int> fp_End = { rand() % 20 + 600, rand() % 10 + 125 };

	std::vector<sf::Vector2f> firstPoints =
		CalcCubicBezier(
			sf::Vector2f(fp_Start[0], fp_Start[1]),
			sf::Vector2f(620, 125),
			sf::Vector2f(100, 100),
			sf::Vector2f(fp_End[0], fp_End[1]),
			25);

	std::vector<sf::Vector2f> secondPoints =
		CalcCubicBezier(
			sf::Vector2f(fp_End[0], fp_End[1]),
			sf::Vector2f(1050, 435),
			sf::Vector2f(1060, 175),
			sf::Vector2f(1050, 435),
			25);

	std::vector<sf::Vector2f> thirdPoints =
		CalcCubicBezier(
			sf::Vector2f(1050, 435),
			sf::Vector2f(750, 950),
			sf::Vector2f(1100, 850),
			sf::Vector2f(750, 950),
			25);

	std::vector<sf::Vector2f> fourthPoints =
		CalcCubicBezier(
			sf::Vector2f(750, 950),
			sf::Vector2f(250, 600),
			sf::Vector2f(300, 1050),
			sf::Vector2f(250, 600),
			25);

	vectorOfPoints.push_back(firstPoints);
	vectorOfPoints.push_back(secondPoints);
	vectorOfPoints.push_back(thirdPoints);
	vectorOfPoints.push_back(fourthPoints);

	// Append the points as vertices to the vertex array
	for (int i = 0; i < vectorOfPoints.size(); ++i) {
		for (std::vector<sf::Vector2f>::const_iterator a = vectorOfPoints[i].begin(); a != vectorOfPoints[i].end(); ++a) {
			vertices.append(sf::Vertex(*a, sf::Color::White));
		}
	}

	std::vector<sf::Vector2f> pointsToFollowForEnemy;

	if (pointsToFollowForEnemy.size() == 0) {
		for (int i = 0; i < vertices.getVertexCount(); ++i) {
			sf::Vector2f temporaryPoint = { vertices[i].position.x, vertices[i].position.y };
			pointsToFollowForEnemy.push_back(temporaryPoint);
		}
	}
	this->setPointsToFollow(pointsToFollowForEnemy);
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
