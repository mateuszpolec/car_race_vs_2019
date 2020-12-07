#include "player_class.h"

Player::Player(std::string authtoken) :
	m_token(authtoken), 
	jsonWorker(new JSONWorker()) {}



sf::Sprite Player::getPlayerSpriteObject() {
	this->playerTexture.loadFromFile("./Assets/car_sprite_1.png");
	this->player.setTexture(this->playerTexture);
	this->player.setScale(3.0, 3.0);
	this->player.setOrigin(4.5f, 7.0f);
	return this->player;
}

void Player::listenPlayerMove() {
	float deltaTime = this->clock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (this->currentSpeed < Options::s_maxVelocity) {
			this->currentSpeed += Options::s_maxAcceleration * deltaTime;
		}
	}
	else {
		this->currentSpeed -= Options::s_frictionForce * deltaTime;
		if (this->currentSpeed < 0.f) {
			this->currentSpeed = 0.f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->currentSpeed -= Options::s_maxDeceleration * deltaTime;
		if (this->currentSpeed < 0.f) {
			this->currentSpeed = 0.f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (this->currentSpeed > 0) {
			this->player.rotate(-Options::s_rotateAmmount * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (this->currentSpeed > 0) {
			this->player.rotate(Options::s_rotateAmmount * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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


	sf::Vector2f oldVector = this->movementVector;
	sf::Transform transform;

	transform.rotate(this->player.getRotation());
	this->movementVector = transform.transformPoint(this->forwardVector);

	this->currentSpeed *= Options::mathDotProductCalculation(oldVector, this->movementVector);

	//std::cout << this->player.getRotation() << std::endl;

	this->player.move(this->movementVector * this->currentSpeed * 0.05f);

	std::cout << "Player pos: " << this->player.getPosition().x << " " << this->player.getPosition().y << "\n";
	
}

sf::Vector2f Player::getPlayerPosition() {
	return this->player.getPosition();
}

//MADE A CONST FOR TILE SIZE
int Player::getPlayerPositionX() {
	return std::abs( (int) this->player.getPosition().x / 12);
}

int Player::getPlayerPositionY() {
	return std::abs((int) this->player.getPosition().y / 12);
}

void Player::checkPlayerCollision(std::uint32_t tileID) {
	if (tileID == Options::s_GrassTileID) {
		//Options::setVelocityAndAccelerationForGrass();
		//if (this->currentSpeed > Options::s_maxVelocity) {
		//	this->currentSpeed -= Options::grasss_frictionForce * 0.07f;
		//}
	}
	else {
		if (!this->isHandbrakeOn) {
			Options::setVelocityAndAccelerationForAsphalt();
		}
	}

	if (tileID == Options::s_checkpointOneTleID) {
		this->checkpointsReached.insert(1);
	}
	else if (tileID == Options::s_checkpointTwoTileID) {
		this->checkpointsReached.insert(2);
	}
	else if (tileID == Options::s_checkpointThreeTileID) {
		this->checkpointsReached.insert(3);
	}

	if (tileID == Options::s_StartblockTileID) {
		if (this->checkpointsReached.size() == 3) {
			this->isNextLap = true;
		}
	}
	else {
		if (this->isNextLap == true) {
			this->checkpointsReached.clear();
			this->isNextLap = false;
		}
	}

}

std::string Player::getMyToken() {
	return m_token;
}

void Player::moveToStart() {
	this->player.rotate(180.f);
	this->player.setPosition(250, 600);
}
