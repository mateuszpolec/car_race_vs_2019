#include "player_class.h"

Player::Player(std::string authtoken) {
	token = authtoken;
}

inline void Player::getMyVelocity() {
	std::cout << "My position is: " << playerVelocity.x << " " << playerVelocity.y << std::endl;
}

sf::CircleShape Player::getMySpriteObject() {
    player.setRadius(10);
    player.setFillColor(sf::Color::Green);
    return player;
}

void Player::listenPlayerMove() {
    float deltaTime = clock.restart().asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        playerVelocity.y -= playerAcceleration.y * deltaTime;
        playerAcceleration.y += 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        playerVelocity.y += playerAcceleration.y * deltaTime;
        playerAcceleration.y += 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerVelocity.x -= playerAcceleration.x * deltaTime;
        playerAcceleration.x += 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerVelocity.x += playerAcceleration.x * deltaTime;
        playerAcceleration.x += 3;
    }
}

void Player::movePlayer() {
    float deltaTime = clock.restart().asSeconds();
    playerPosition += playerVelocity * deltaTime;
    this->player.setPosition(playerPosition);
}

std::string Player::getMyToken() {
    return token;
}