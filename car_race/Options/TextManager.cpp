#include "./TextManager.h"

sf::Text qualificationLapsText(sf::Font& gameFont, sf::Vector2f playerPosition) {
	sf::Text text;
	text.setFont(gameFont);
	text.setString("Qualification round!");
	text.setCharacterSize(18);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(playerPosition.x - (sizeOfText.width / 2), playerPosition.y - 250);
	return text;
}

sf::Text qualificationLapsHelpText(sf::Font& gameFont, sf::Vector2f playerPosition) {
	sf::Text text;
	text.setFont(gameFont);
	text.setString("You have to do three laps as fast as possible, \n it is going to determine on which place you are going to start main race.");
	text.setCharacterSize(14);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(playerPosition.x - (sizeOfText.width/2), playerPosition.y - 200);
	return text;
}