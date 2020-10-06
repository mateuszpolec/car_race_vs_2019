#include <iostream>
#include <SFML/Graphics.hpp>

/**
* Class Player - handle information about player
* 
*/
class Player {
    int x;
    int y;
    std::string token;
    sf::CircleShape player; //Generate player object

public:
    /**
    * Constructor
    * @param x_position - X-axis player position
    * @param y_position - Y-axis player position
    * @param authtoken - Authentication token for API communication
    */

    Player(int x_position, int y_position, std::string authtoken) {
        x = x_position;
        y = y_position;
        token = authtoken;
    };

    void getMyPosition() {
        std::cout << "My position is: " << x << " " << y << std::endl;
    }

    sf::CircleShape getMySpriteObject() {
        player.setRadius(10);
        player.setFillColor(sf::Color::Green);
        return player;
    }


    void getMyToken() {
        std::cout << "My token is: " << token << std::endl;
    }
};