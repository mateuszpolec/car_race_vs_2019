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
	sf::Vector2f pointToGo = this->pointsToFollow[this->actualPointToGo]; //Choose point to go
	sf::Vector2f oldPosition = this->enemy.getPosition();

	//Acceleration
	if (this->currentSpeed < Options::s_maxVelocity) {
		this->currentSpeed += Options::s_maxAcceleration * deltaTime;
	}
	
	//Cartesian system to polar system
	float r = sqrt(pow((pointToGo.x - oldPosition.x), 2) + pow((pointToGo.y - oldPosition.y), 2));
	float x = pointToGo.x - oldPosition.x;
	float angle_sin = asin(x / r) * 180.0 / 3.14;

	//Set half of plot, because sinus is positive in scope of <0; 270> and negative in scope of (270; 360>
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



	//The magic of moving player
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

void Enemy::checkEnemyCollision(std::uint32_t tileID) {
	if (tileID == Options::s_GrassTileID) {
		if (this->currentSpeed > 120) {
			this->currentSpeed -= Options::s_Grass_frictionForce * 0.08f;
		}
	}
}

void Enemy::createTrack() {
	sf::VertexArray vertices(sf::LinesStrip, 0);

	std::vector<std::vector<sf::Vector2f>> vectorOfPoints;
	// Calculate the points on the curve (10 segments)

	Enemy::nextRandomBezierPoint firstPoint(rand() % 100 + 250, rand() % 25 + 575);
	Enemy::nextRandomBezierPoint firstCurve(rand() % 200 + 75, rand() % 25 + 75);
	Enemy::nextRandomBezierPoint secondPoint(rand() % 20 + 600, rand() % 10 + 125);
	Enemy::nextRandomBezierPoint secondCurve(rand() % 200 + 1060, rand() % 25 + 175);
	Enemy::nextRandomBezierPoint thirdPoint(rand() % 100 + 945, rand() % 30 + 435);
	Enemy::nextRandomBezierPoint thirdCurve(rand() % 200 + 1025, rand() % 25 + 850);
	Enemy::nextRandomBezierPoint fourthPoint(rand() % 100 + 650, rand() % 100 + 850);
	Enemy::nextRandomBezierPoint fourthCurve(rand() % 100 + 275, rand() % 25 + 1000);


	std::vector<sf::Vector2f> firstPoints =
		CalcCubicBezier(
			sf::Vector2f(firstPoint.x, firstPoint.y),
			sf::Vector2f(secondPoint.x, secondPoint.y),
			sf::Vector2f(firstCurve.x, firstCurve.y),
			sf::Vector2f(secondPoint.x, secondPoint.y),
			25);

	std::vector<sf::Vector2f> secondPoints =
		CalcCubicBezier(
			sf::Vector2f(secondPoint.x, secondPoint.y),
			sf::Vector2f(thirdPoint.x, thirdPoint.y),
			sf::Vector2f(secondCurve.x, secondCurve.y),
			sf::Vector2f(thirdPoint.x, thirdPoint.y),
			25);

	std::vector<sf::Vector2f> thirdPoints =
		CalcCubicBezier(
			sf::Vector2f(thirdPoint.x, thirdPoint.y),
			sf::Vector2f(fourthPoint.x, fourthPoint.y),
			sf::Vector2f(thirdCurve.x, thirdCurve.y),
			sf::Vector2f(fourthPoint.x, fourthPoint.y),
			25);

	std::vector<sf::Vector2f> fourthPoints =
		CalcCubicBezier(
			sf::Vector2f(fourthPoint.x, fourthPoint.y),
			sf::Vector2f(firstPoint.x, firstPoint.y),
			sf::Vector2f(fourthCurve.x, fourthCurve.y),
			sf::Vector2f(firstPoint.x, firstPoint.y),
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

	// Change from VertexArray to Standard Libary Vector with Vector2f
	if (pointsToFollowForEnemy.size() == 0) {
		for (int i = 0; i < vertices.getVertexCount(); ++i) {
			sf::Vector2f temporaryPoint = { vertices[i].position.x, vertices[i].position.y };
			pointsToFollowForEnemy.push_back(temporaryPoint);
		}
	}

	this->setPointsToFollow(pointsToFollowForEnemy);
}



int Enemy::getEnemyPositionX() {
	return std::abs((int) this->enemy.getPosition().x / 12);
}

int Enemy::getEnemyPositionY() {
	return std::abs((int)this->enemy.getPosition().y / 12);
}
