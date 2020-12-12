#include "enemy.h"
#include "../FileWorker/sfml_layer_loader.h"

Enemy::Enemy(std::string name) : m_Name(name) {}

Enemy::~Enemy() {}

sf::Sprite Enemy::getEnemySpriteObject() {
	if (this->textureIsLoaded == false) {
		this->textureIsLoaded = true;
		short randInt = rand() % 7;
		this->enemyTexture.loadFromFile(Options::pathsToTextures[randInt]);
		m_Enemy.setTexture(this->enemyTexture);
		m_Enemy.setScale(3.0, 3.0);
		m_Enemy.setOrigin(4.5f, 7.0f);
		return m_Enemy;
	}
	else {
		return m_Enemy;
	}
}

void Enemy::moveToStart() {
	int xPosition = rand() % 175 + 175;
	int yPosition = rand() % 200 + 575;
	this->m_Enemy.rotate(180.f);
	this->m_Enemy.setPosition(525, 1270);
}

void Enemy::moveEnemy() {
	float deltaTime = this->clock.restart().asSeconds();
	sf::Vector2f pointToGo = this->pointsToFollow[this->actualPointToGo]; //Choose point to go
	sf::Vector2f oldPosition = this->m_Enemy.getPosition();

	std::cout << this->actualPointToGo << "\n";

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
		this->m_Enemy.setRotation(180 + angle_sin);
	}

	if (this->actualPointToGo == 24) {
		this->halfOfPlot = 1;
	}

	if (this->halfOfPlot == 1) {
		this->m_Enemy.setRotation(360 - angle_sin);
	}

	//Slowing down enemy for sharp turn in given place on map
	if (this->actualPointToGo > 78 && this->actualPointToGo < 100) {
		if (this->currentSpeed > 200) {
			this->currentSpeed -= Options::s_Grass_frictionForce * 0.08f;
		}

	}

	if (this->actualPointToGo == 128) {
		this->halfOfPlot = 0;
	}

	//if (this->actualPointToGo == 104) {
	//	this->halfOfPlot = 0;
	//}

	//The magic of moving player
	sf::Vector2f oldVector = this->movementVector;
	sf::Transform transform;

	transform.rotate(this->m_Enemy.getRotation());
	this->movementVector = transform.transformPoint(this->forwardVector);


	this->m_Enemy.move(this->movementVector * this->currentSpeed * 0.05f);

	if (r < 150) {
		this->actualPointToGo++;
		this->tooFar = false;
		if (this->actualPointToGo > 148) {
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
			std::cout << m_Name << " Collision" << "\n";
			this->currentSpeed -= Options::s_Grass_frictionForce * 0.08f;
		}
	}
}

void Enemy::checkCollisionInBezier() {
	std::cout << "Called" << "\n";
}

void Enemy::createTrack() {
	 sf::VertexArray vertices(sf::LinesStrip, 0);

	std::vector<std::vector<sf::Vector2f>> vectorOfPoints;
	// Calculate the points on the curve (10 segments)
			
	Enemy::nextRandomBezierPoint firstPoint(rand() % 100 + 425, rand() % 100 + 1092);
	Enemy::nextRandomBezierPoint firstCurve(372, 456);
	Enemy::nextRandomBezierPoint secondPoint(rand() % 100 + 1272, rand() % 100 + 492);
	Enemy::nextRandomBezierPoint secondCurve(2004, 468);
	Enemy::nextRandomBezierPoint thirdPoint(rand() % 100 + 1728, rand() % 100 + 1128);
	Enemy::nextRandomBezierPoint thirdCurve(1896, 1740);
	Enemy::nextRandomBezierPoint fourthPoint(rand() % 100 + 1596, rand() % 100 + 1500);
	Enemy::nextRandomBezierPoint fourthCurve(1140, 1560);
	Enemy::nextRandomBezierPoint fifthPoint(rand() % 100 + 1368, rand() % 100 + 1716);
	Enemy::nextRandomBezierPoint fifthCurve(1584, 2076);
	Enemy::nextRandomBezierPoint sixthPoint(rand() % 100 + 1020, rand() % 100 + 1920);
	Enemy::nextRandomBezierPoint sixthCurve(312, 1944);

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
			sf::Vector2f(fifthPoint.x, fifthPoint.y),
			sf::Vector2f(fourthCurve.x, fourthCurve.y),
			sf::Vector2f(fifthPoint.x, fifthPoint.y),
			25);

	std::vector<sf::Vector2f> fifthPoints =
		CalcCubicBezier(
			sf::Vector2f(fifthPoint.x, fifthPoint.y),
			sf::Vector2f(sixthPoint.x, sixthPoint.y),
			sf::Vector2f(fifthCurve.x, fifthCurve.y),
			sf::Vector2f(sixthPoint.x, sixthPoint.y),
			25);

	std::vector<sf::Vector2f> sixthPoints =
		CalcCubicBezier(
			sf::Vector2f(sixthPoint.x, sixthPoint.y),
			sf::Vector2f(firstPoint.x, firstPoint.y),
			sf::Vector2f(sixthCurve.x, sixthCurve.y),
			sf::Vector2f(firstPoint.x, firstPoint.y),
			25);

	vectorOfPoints.push_back(firstPoints);
	vectorOfPoints.push_back(secondPoints);
	vectorOfPoints.push_back(thirdPoints);
	vectorOfPoints.push_back(fourthPoints);
	vectorOfPoints.push_back(fifthPoints);
	vectorOfPoints.push_back(sixthPoints);



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
	return std::abs((int) this->m_Enemy.getPosition().x / 12);
}

int Enemy::getEnemyPositionY() {
	return std::abs((int)this->m_Enemy.getPosition().y / 12);
}
