#include "player_class.h"

Player::Player(std::string authtoken) {
	token = authtoken;
}

void Player::getMyVelocity() {
	std::cout << "My velocity is: " << m_playerVelocity.x << " " << m_playerVelocity.y << std::endl;
}


sf::CircleShape Player::getMySpriteObject() {
	m_player.setRadius(10);
	m_player.setFillColor(sf::Color::Green);
	return m_player;
}

void Player::listenPlayerMove() {
	float deltaTime = clock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		//Checking if player velocity is not too high
		if (m_playerVelocity.y > -Options::playerMaxVelocityYAxis) {
			m_playerVelocity.y -= m_playerAcceleration.x * deltaTime;
		}
		if (m_playerAcceleration.y < Options::playerMaxAccelerationYAxis) {
			m_playerAcceleration.y += 3;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (m_playerVelocity.y < Options::playerMaxVelocityYAxis) {
			m_playerVelocity.y += m_playerAcceleration.x * deltaTime;
		}				
		if (m_playerAcceleration.y < Options::playerMaxAccelerationYAxis) {
			m_playerAcceleration.y += 3;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (m_playerVelocity.x > -Options::playerMaxVelocityXAxis) {
			m_playerVelocity.x -= m_playerAcceleration.x * deltaTime;
		}		
		if (m_playerAcceleration.x < Options::playerMaxAccelerationYAxis) {
			m_playerAcceleration.x += 3;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (m_playerVelocity.x < Options::playerMaxVelocityXAxis) {
			m_playerVelocity.x += m_playerAcceleration.x * deltaTime;
		}
		if (m_playerAcceleration.x < Options::playerMaxAccelerationYAxis) {
			m_playerAcceleration.x += 3;
		}
	}
}


void Player::movePlayer() {
	float tickRate = 0.0050;
	m_playerPosition += m_playerVelocity * tickRate;
	this->m_player.setPosition(m_playerPosition);
}

sf::Vector2f Player::getMyPosition() {
	return m_playerPosition;
}

int Player::getMyPositionX() {
	return std::abs((int) m_playerPosition.x / 12);
}

int Player::getMyPositionY() {
	return std::abs((int) m_playerPosition.y / 12);
}

std::string Player::getMyToken() {
	return token;
}
