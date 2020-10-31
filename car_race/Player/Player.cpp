#include "player_class.h"

Player::Player(std::string authtoken) {
	token = authtoken;
}

void Player::getMyVelocity() {
	std::cout << "My velocity is: " << m_currentSpeed << std::endl;
}


sf::Sprite Player::getMySpriteObject() {
	this->m_playerTexture.loadFromFile("./Assets/car_spirit_1.png");
	m_player.setTexture(this->m_playerTexture);
	m_player.setScale(3.0, 3.0);
	m_player.setOrigin(4.5f, 7.0f);
	return m_player;
}

void Player::listenPlayerMove() {
	float deltaTime = clock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_player.rotate(-Options::playerRotateAmmount * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_player.rotate(Options::playerRotateAmmount * deltaTime);
	}
}


void Player::movePlayer() {

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

std::string Player::getMyToken() {
	return token;
}
