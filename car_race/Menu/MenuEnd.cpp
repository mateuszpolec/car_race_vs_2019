#include "MenuEnd.h"

sf::RectangleShape menuEndBackground() {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(s_screenWidth, s_screenHeight));
	rectangle.setFillColor(sf::Color(67, 166, 40));
	rectangle.setPosition(0, 0);
	return rectangle;
}

sf::RectangleShape menuEndBackground2() {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(s_screenWidth - 150, s_screenHeight - 150));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(75, 75);
	return rectangle;
}

sf::Sprite menuEndCup() {
	static sf::Texture cupTexture;
	sf::Sprite cup;
	cupTexture.loadFromFile("./Assets/cup.png");
	cup.setTexture(cupTexture);
	cup.setScale(0.25f, 0.25f);
	sf::FloatRect sizeOfCup = cup.getGlobalBounds();
	cup.setPosition((s_screenWidth / 2) - (sizeOfCup.width / 2), (s_screenHeight / 2) - 150);
	return cup;
}