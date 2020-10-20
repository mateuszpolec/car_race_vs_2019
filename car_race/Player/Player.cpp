#include "player_class.h"

Player::Player(std::string authtoken) {
	token = authtoken;
}

inline void Player::getMyVelocity() {
	std::cout << "My position is: " << m_playerVelocity.x << " " << m_playerVelocity.y << std::endl;
}


sf::CircleShape Player::getMySpriteObject() {
    m_player.setRadius(10);
    m_player.setFillColor(sf::Color::Green);
    return m_player;
}

void Player::listenPlayerMove() {
    float deltaTime = clock.restart().asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_playerVelocity.y -= m_playerAcceleration.y * deltaTime;
        m_playerAcceleration.y += 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_playerVelocity.y += m_playerAcceleration.y * deltaTime;
        m_playerAcceleration.y += 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_playerVelocity.x -= m_playerAcceleration.x * deltaTime;
        m_playerAcceleration.x += 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_playerVelocity.x += m_playerAcceleration.x * deltaTime;
        m_playerAcceleration.x += 3;
    }
}

void Player::movePlayer() {
    float deltaTime = clock.restart().asSeconds();
    m_playerPosition += m_playerVelocity * deltaTime;
    this->m_player.setPosition(m_playerPosition);
}

sf::Vector2f Player::getMyPosition() {
    return m_playerPosition;
}

std::string Player::getMyToken() {
    return token;
}