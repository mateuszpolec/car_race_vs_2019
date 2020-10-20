#include "player_camera.h"

PlayerCamera::PlayerCamera() {
	this->followPlayer.setSize(1200.f, 800.f);
}

void PlayerCamera::cameraFollowPlayer(sf::RenderWindow& window, sf::Vector2f playerPosition) {
	window.setView(this->followPlayer);
	this->followPlayer.setCenter(playerPosition);
}