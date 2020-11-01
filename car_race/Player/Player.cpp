#include "player_class.h"

Player::Player(std::string authtoken) {
	token = authtoken;
}

void Player::getMyVelocity() {
	std::cout << "My velocity is: " << m_currentSpeed << std::endl;
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
		//TODO IDEA: Create a function for drifting - hand brake
		//Descripiton of movement:

		// If player moving LEFT: -x
		// If player is moving RIGHT: +x
		// If player is moving UP: -y
		// If player is moving DOWN: +y
	}

}


void Player::movePlayer() {


	sf::Vector2f oldVector = m_movmentVector;
	sf::Transform transform;

	transform.rotate(m_player.getRotation());
	m_movmentVector = transform.transformPoint(m_forwardVector);

	std::cout << " Movement vector: " << m_movmentVector.x << " " << m_movmentVector.y << std::endl;

	m_currentSpeed *= Options::mathDotProductCalculation(oldVector, m_movmentVector);

	std::cout << " Current speed " << m_currentSpeed << std::endl;

	m_player.move(m_movmentVector * m_currentSpeed * 0.05f);
	

}

sf::Vector2f Player::getMyPosition() {
	return m_player.getPosition();
}

//MADE A CONST FOR TILE SIZE
int Player::getMyPositionX() {
	return std::abs((int) m_player.getPosition().x / 12);
}

int Player::getMyPositionY() {	
	return std::abs((int) m_player.getPosition().y / 12);
}

void Player::checkPlayerCollision(std::uint32_t tileID) {
	if (tileID == Options::GrassTileID) {
		Options::setVelocityAndAccelerationForGrass();
		if (m_currentSpeed > Options::playerMaxVelocity) {
			m_currentSpeed -= Options::grassFrictionForce * 0.07f;
		}
	}
	else {
		Options::setVelocityAndAccelerationForAsphalt();
	}
}

std::string Player::getMyToken() {
	return token;
}
