#include <iostream>
#include <SFML/Graphics.hpp>

/**
* Class Player - handle information about player
* 
*/
class Player {
    std::string token;
    sf::Vector2f playerPosition = { 1, 1 };
    sf::Vector2f playerVelocity = { 1, 1 }; //To remember, Vector2f dont use notation like arrays but notation like Cartesian system
    sf::Vector2f playerAcceleration = { 2500, 2500 };
    sf::CircleShape player; //Generate player object
    sf::Clock clock;

public:
    /**
    * Constructor
    * @param authtoken - Authentication token for API communication
    */

    Player(std::string authtoken) {
        token = authtoken;
    };

    /**
    * getMyVelocity
    * Function created only for test, to check how fast player moves
    * void function, no params
    */
    void getMyVelocity() {
        std::cout << "My position is: " << playerVelocity.x << " " << playerVelocity.y << std::endl;
    }

    /**
    * getMySpriteObject
    * Function returns player sprite object, like shape, color
    * @param - 
    * @return - SFML CircleShape player object
    */
    sf::CircleShape getMySpriteObject() {
        player.setRadius(10);
        player.setFillColor(sf::Color::Green);
        return player;
    }

    void listenPlayerMove() {
        float deltaTime = clock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerVelocity.y -= playerAcceleration.y * deltaTime;
            playerAcceleration.y += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerVelocity.y += playerAcceleration.y * deltaTime;
            playerAcceleration.y += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerVelocity.x -= playerAcceleration.x * deltaTime;
            playerAcceleration.x += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerVelocity.x += playerAcceleration.x * deltaTime;
            playerAcceleration.x += 5;
        }
    }

    void movePlayer() {
        float deltaTime = clock.restart().asSeconds();
        std::cout << "Player velocity is: " << playerVelocity.x << ", " << playerVelocity.y << std::endl;
        playerPosition += playerVelocity * deltaTime;
        this->player.setPosition(playerPosition);
    }

    /**
    * getMyToken
    * Function for tests to print player token
    * void function no params
    */
    void getMyToken() {
        std::cout << "My token is: " << token << std::endl;
    }
};