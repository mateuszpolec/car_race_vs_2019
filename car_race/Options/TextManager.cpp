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
	text.setString("You have to do three laps as fast as possible,\nit is going to determine on which place you are going to start main race.");
	text.setCharacterSize(14);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(playerPosition.x - (sizeOfText.width/2), playerPosition.y - 200);
	return text;
}

sf::Text mainRaceLapsText(sf::Font& gameFont, sf::Vector2f playerPosition) {
	sf::Text text;
	text.setFont(gameFont);
	text.setString("Race round!");
	text.setCharacterSize(18);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(playerPosition.x - (sizeOfText.width / 2) - 350, playerPosition.y - 250);
	return text;
}

sf::Text mainRaceLapsHelpText(sf::Font& gameFont, sf::Vector2f playerPosition) {
	sf::Text text;
	text.setFont(gameFont);
	text.setString("That's the main race round!\nYou have to drive as fast as possible\nand complete all 10 laps to win the race.\nEveryone is starting on position\nthat they won in qualification round.\nGood luck!");
	text.setCharacterSize(14);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(playerPosition.x - (sizeOfText.width / 2) - 305, playerPosition.y - 200);
	return text;

}

sf::Text timeCountdownText(sf::Font& gameFont, sf::Vector2f playerPosition, float time) {
	sf::Text text;
	text.setFont(gameFont);
	int timeToInt = (int) time;
	std::string timeToString = std::to_string(timeToInt);
	text.setString(timeToString);
	text.setCharacterSize(16);
	sf::FloatRect sizeOfText = text.getGlobalBounds();
	text.setFillColor(sf::Color::White);
	text.setPosition(playerPosition.x - (sizeOfText.width / 2), playerPosition.y - 100);
	return text;
}