#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H


#include <SFML/Graphics.hpp>
#include "../Options/options.h"


const sf::Vector2f centerOfScreen = { s_screenHeight / 2, s_screenWidth / 2 };

sf::Text qualificationLapsText(sf::Font& gameFont, sf::Vector2f playerPosition);
sf::Text qualificationLapsHelpText(sf::Font& gameFont, sf::Vector2f playerPosition);


#endif