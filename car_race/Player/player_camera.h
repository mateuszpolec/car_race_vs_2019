#include <SFML/Graphics.hpp>

class PlayerCamera {
	public:

		sf::View followPlayer;

		PlayerCamera();

		void cameraFollowPlayer(sf::RenderWindow& window, sf::Vector2f playerPosition);
};