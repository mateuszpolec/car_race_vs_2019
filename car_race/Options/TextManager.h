#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H


#include <SFML/Graphics.hpp>
#include "../Options/options.h"


const sf::Vector2f centerOfScreen = { s_screenHeight / 2, s_screenWidth / 2 };

//TODO: Documentation
sf::Text qualificationLapsText(sf::Font& gameFont, sf::Vector2f playerPosition);
//TODO: Documentation
sf::Text qualificationLapsHelpText(sf::Font& gameFont, sf::Vector2f playerPosition);
//TODO: Documentation
sf::Text timeCountdownText(sf::Font& gameFont, sf::Vector2f playerPosition, std::string time);


#endif