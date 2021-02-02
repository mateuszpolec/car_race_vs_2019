#include "Player.h"

Player::Player(std::string authtoken) :
	m_token(authtoken) {}



sf::Sprite Player::getPlayerSpriteObject() {
	this->m_playerTexture.loadFromFile("./Assets/car_sprite_1.png");
	this->m_player.setTexture(this->m_playerTexture);
	this->m_player.setScale(3.0f, 3.0f);
	this->m_player.setOrigin(4.5f, 7.0f);
	return this->m_player;
}

void Player::listenPlayerMove() {
	float deltaTime = this->m_clock.restart().asSeconds();
	this->m_timeCounter += deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (this->m_currentSpeed < s_maxVelocity) {
			this->m_currentSpeed += s_maxAcceleration * deltaTime;
		}
	}
	else {
		this->m_currentSpeed -= s_frictionForce * deltaTime;
		if (this->m_currentSpeed < 0.f) {
			this->m_currentSpeed = 0.f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->m_currentSpeed -= s_maxDeceleration * deltaTime;
		if (this->m_currentSpeed < 0.f) {
			this->m_currentSpeed = 0.f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (this->m_currentSpeed > 0) {
			this->m_player.rotate(-s_rotateAmmount * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (this->m_currentSpeed > 0) {
			this->m_player.rotate(s_rotateAmmount * deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->m_isHandbrakeOn = true;
		//TODO IDEA: Create a function for drifting - hand brake
		//Descripiton of movement:

		// If player moving LEFT: -x
		// If player is moving RIGHT: +x
		// If player is moving UP: -y
		// If player is moving DOWN: +y
	}
	else {
		this->m_isHandbrakeOn = false;
	}

}


void Player::movePlayer() {


	sf::Vector2f oldVector = this->m_movementVector;
	sf::Transform transform;

	transform.rotate(this->m_player.getRotation());
	this->m_movementVector = transform.transformPoint(this->m_forwardVector);

	this->m_currentSpeed *= mathDotProductCalculation(oldVector, this->m_movementVector);

	//std::cout << this->player.getRotation() << std::endl;

	this->m_player.move(this->m_movementVector * this->m_currentSpeed * 0.05f);
	
}

sf::Vector2f Player::getPlayerPosition() {
	return this->m_player.getPosition();
}

//MADE A CONST FOR TILE SIZE
int Player::getPlayerPositionX() {
	return std::abs((int) this->m_player.getPosition().x / s_tileSize);
}

int Player::getPlayerPositionY() {
	return std::abs((int) this->m_player.getPosition().y / s_tileSize);
}

void Player::checkPlayerCollision(std::uint32_t tileID) {
	if (tileID == s_GrassTileID) {
		if (this->m_currentSpeed > 120) {
			this->m_currentSpeed -= s_Grass_frictionForce * 0.08f;
		}
	}
	else {
		if (!this->m_isHandbrakeOn) {}
	}

	if (tileID == s_checkpointOneTleID) {
		this->checkpointsReached.insert(1);
		std::cout << "FIRST CHECKPOINT IN" << "\n";
	}
	else if (tileID == s_checkpointTwoTileID) {
		this->checkpointsReached.insert(2);
		std::cout << "SECOND CHECKPOINT IN" << "\n";
	}
	else if (tileID == s_checkpointThreeTileID) {
		this->checkpointsReached.insert(3);
		std::cout << "THIRD CHECKPOINT IN" << "\n";
	}

	if (tileID == s_StartblockTileID) {
		if (this->checkpointsReached.size() == 3) {
			this->m_isNextLap = true;
		}
	}
	else {
		if (this->m_isNextLap == true) {
			std::cout << "NEXT LAP IN" << "\n";
			this->checkpointsReached.clear();
			this->currentLap++;
			this->m_isNextLap = false;
		}
	}
}

sf::Text Player::showName(sf::Font& gameFont) {
	sf::Text text;
	text.setFont(gameFont);
	text.setString("Player");
	text.setCharacterSize(18);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(this->m_player.getPosition().x - (sizeOfText.width / 2), this->m_player.getPosition().y - 70);
	return text;
}

sf::Text Player::showLap(sf::Font& gameFont, int lapsToGo) {
	sf::Text text;
	text.setFont(gameFont);
	std::string laps = "Laps: " + std::to_string(this->currentLap) + " / " + std::to_string(lapsToGo);
	text.setString(laps);
	text.setCharacterSize(14);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(this->m_player.getPosition().x - (sizeOfText.width / 2), this->m_player.getPosition().y - 50);
	return text;

}

std::string Player::getMyToken() {
	return m_token;
}

void Player::moveToStart() {
	this->m_player.rotate(180.f);
	this->m_player.setPosition(525, 1270);
}

void Player::moveToStartPosition() {
	this->m_player.setRotation(180.f);
	this->m_player.setPosition(startingPlace);
}

void Player::moveToZeroPosition() {
	this->m_player.setPosition(s_screenWidth / 2, s_screenHeight / 2);
}