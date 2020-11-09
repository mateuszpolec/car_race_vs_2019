#include "player_class.h"

Player::Player(std::string authtoken) {
	token = authtoken;
	this->actualFrame = 0;
	this->jsonWorker = new JSONWorker();
}

Player::~Player() {
	delete this->jsonWorker;
}


void Player::recordPlayerMove() {
	this->actualFrame++;
	this->jsonWorker->sendPlayerRecordedData(this->actualFrame, this->m_currentSpeed, this->m_player.getRotation());
}


sf::Sprite Player::getMySpriteObject() {
	this->m_playerTexture.loadFromFile("./Assets/car_sprite_1.png");
	m_player.setTexture(this->m_playerTexture);
	m_player.setScale(3.0, 3.0);
	m_player.setOrigin(4.5f, 7.0f);
	return m_player;
}

void Player::listenPlayerMove() {
	float deltaTime = clock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (m_currentSpeed < Options::playerMaxVelocity) {
			m_currentSpeed += Options::playerMaxAcceleration * deltaTime;
		}
	}
	else {
		m_currentSpeed -= Options::playerFrictionForce * deltaTime;
		if (m_currentSpeed < 0.f) {
			m_currentSpeed = 0.f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_currentSpeed -= Options::playerMaxDeceleration * deltaTime;
		if (m_currentSpeed < 0.f) {
			m_currentSpeed = 0.f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (m_currentSpeed > 0) {
			m_player.rotate(-Options::playerRotateAmmount * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (m_currentSpeed > 0) {
			m_player.rotate(Options::playerRotateAmmount * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Options::playerMaxAcceleration = 0.f;
		std::cout << Options::playerMaxAcceleration << std::endl;
		this->isHandbrakeOn = true;
		//TODO IDEA: Create a function for drifting - hand brake
		//Descripiton of movement:

		// If player moving LEFT: -x
		// If player is moving RIGHT: +x
		// If player is moving UP: -y
		// If player is moving DOWN: +y
	}
	else {
		this->isHandbrakeOn = false;
	}

}


void Player::movePlayer() {


	sf::Vector2f oldVector = m_movmentVector;
	sf::Transform transform;

	transform.rotate(m_player.getRotation());
	m_movmentVector = transform.transformPoint(m_forwardVector);

	m_currentSpeed *= Options::mathDotProductCalculation(oldVector, m_movmentVector);

	m_player.move(m_movmentVector * m_currentSpeed * 0.05f);
	
}

sf::Vector2f Player::getMyPosition() {
	return m_player.getPosition();
}

//MADE A CONST FOR TILE SIZE
int Player::getMyPositionX() {
	return std::abs( (int) m_player.getPosition().x / 12);
}

int Player::getMyPositionY() {	
	return std::abs((int) m_player.getPosition().y / 12);
}

void Player::checkPlayerCollision(std::uint32_t tileID) {
	this->recordPlayerMove();
	if (tileID == Options::GrassTileID) {
		Options::setVelocityAndAccelerationForGrass();
		if (m_currentSpeed > Options::playerMaxVelocity) {
			m_currentSpeed -= Options::grassFrictionForce * 0.07f;
		}
	}
	else {
		if (!this->isHandbrakeOn) {
			Options::setVelocityAndAccelerationForAsphalt();
		}
	}

	if (tileID == Options::checkpointOneTleID) {
		this->checkpointsReached.insert(1);
	}
	else if (tileID == Options::checkpointTwoTileID) {
		this->checkpointsReached.insert(2);
	}
	else if (tileID == Options::checkpointThreeTileID) {
		this->checkpointsReached.insert(3);
	}

	if (tileID == Options::StartblockTileID) {
		if (this->checkpointsReached.size() == 3) {
			this->m_isNextLap = true;
		}
	}
	else {
		if (this->m_isNextLap == true) {
			this->m_currentLap += 1;
			this->checkpointsReached.clear();
			this->m_isNextLap = false;
		}
	}

}

std::string Player::getMyToken() {
	return token;
}

void Player::moveToStart() {
	this->m_player.rotate(180.f);
	this->m_player.setPosition(250, 600);
}
