#include <iostream>
#include <SFML/Graphics.hpp>

/**
* Class Player - handle information about player
* 
*/
class Player {
    std::string token;
    /* To remember, Vector2f describes data like math cartesian system*/
    sf::Vector2f playerPosition = { 1.0f, 1.2f }; // Player position at start
    sf::Vector2f playerVelocity = { 1, 1 }; // How fast player moves atm
    sf::Vector2f playerAcceleration = { 2500, 2500 }; // Player Acceleration
    sf::CircleShape player; //Generate player object
    sf::Clock clock; // Clock created for elapsing time between frames and correct movement of player 
 public:
    /**
    * Constructor
    * @param authtoken - Authentication token for API communication
    */

     Player(std::string authtoken);

    /**
    * getMyVelocity
    * Function created only for test, to check how fast player moves
    * void function, no params
    */
    inline void getMyVelocity();

    /**
    * getMySpriteObject
    * Function returns player sprite object, like shape, color
    * @param -
    * @return player - SFML CircleShape player object
    */
    sf::CircleShape getMySpriteObject();

    /**
    * listenPlayerMove
    * Function listen for keyboard key press, increment the speed of player and acceleration
    */
    void listenPlayerMove();    

    /**
    * movePlayer
    * Function that is called every frame refresh in Main.cpp, allow player to move with given velocity and acceleration
    */
    void movePlayer();

    /**
    * getMyToken
    * Function that returns auth token for API
    * @return token - hashed API Token for Player
    */
    std::string getMyToken();
};