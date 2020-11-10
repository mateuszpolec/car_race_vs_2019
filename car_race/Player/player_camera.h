#ifndef PLAYER_CAMERA_H
#define PLAYER_CAMERA_H

#include <SFML/Graphics.hpp>

class PlayerCamera {
	public:

		sf::View followPlayer;

		/**
		* Constructor
		* sets the camera size
		* TODO: Create a one size for everything in options
		*/
		PlayerCamera();

		/**
		* cameraFollowPLayer
		* Function allows camera to follow the player
		* @param SFML Object RenderWindow & window - reference to main window
		* @param SFML Object Vector2f playerPosition - player position getter from player class
		*/
		void cameraFollowPlayer(sf::RenderWindow& window, sf::Vector2f playerPosition);
};

#endif