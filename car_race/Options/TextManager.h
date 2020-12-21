#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H


#include <SFML/Graphics.hpp>
#include "../Options/options.h"


const sf::Vector2f centerOfScreen = { s_screenHeight / 2, s_screenWidth / 2 };

/**
* qualificationLapsText
* Display the title of the qualification round
* @param SFML Object Font gameFont - Pass the loaded font into function to make it possible to create text
* @param SFML Object Vector playerPosition - Pass player position to make it possible to draw text at center of the visible window
* @return SFML Object Text - Text with font, font size and position
*/
sf::Text qualificationLapsText(sf::Font& gameFont, sf::Vector2f playerPosition);

/**
* qualificationLapsHelpText
* Display the description of the qualification round
* @param SFML Object Font gameFont - Pass the loaded font into function to make it possible to create text
* @param SFML Object Vector playerPosition - Pass player position to make it possible to draw text at center of the visible window
* @return SFML Object Text - Text with font, font size and position
*/
sf::Text qualificationLapsHelpText(sf::Font& gameFont, sf::Vector2f playerPosition);

sf::Text mainRaceLapsText(sf::Font& gameFont, sf::Vector2f playerPosition);

sf::Text mainRaceLapsHelpText(sf::Font& gameFont, sf::Vector2f playerPosition);

/**
* timeCountdownText
* Display the remaining time to start of an event
* @param SFML Object Font gameFont - Pass the loaded font into function to make it possible to create text
* @param SFML Object Vector playerPosition - Pass player position to make it possible to draw text at center of the visible window
* @param std::string time - Representation of time countdown in string to make it possible to convert into SFML Text Object
* @return SFML Object Text - Text with font, font size and position
*/
sf::Text timeCountdownText(sf::Font& gameFont, sf::Vector2f playerPosition, std::string time);


#endif