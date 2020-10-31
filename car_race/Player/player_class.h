#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"

/**
* Class Player - handle information about player
* 
*/
class Player : Options {
    std::string token;
    /* To remember, Vector2f describes data like math cartesian system*/
    sf::Vector2f m_playerPosition = { 1.0f, 1.2f }; // Player position at start
    sf::Vector2f m_playerVelocity = { 1, 1 }; // How fast player moves atm
    sf::Vector2f m_playerAcceleration = { 2500, 2500 }; // Player Acceleration
    sf::Texture m_playerTexture;
    sf::Sprite m_player; //Generate player object
    sf::Clock clock; // Clock created for elapsing time between frames and correct movement of player 
 public:
    /**
    * Constructor
    * @param string authtoken - Authentication token for API communication
    */

     Player(std::string authtoken);

    /**
    * getMyVelocity
    * Function created only for test, to check how fast player moves
    * void function, no params
    */
    void getMyVelocity();

    /**
    * getMyPosition
    * Function that returns player position
    * @return - SFML Object Vector2f with player position on map
    */
    sf::Vector2f getMyPosition();


    /**
    * getMyPositionX
    * Function that returns player position in X axis including size of tile
    * @return ABS int value with player position in X axis
    */
    int getMyPositionX();


    /**
    * getMyPositionY
    * Function that returns player position in Y axis including size of tile
    * @return ABS int value with player position in Y axis
    */
    int getMyPositionY();

    /**
    * getMySpriteObject
    * Function returns player sprite object, like shape, color
    * @param -
    * @return SFML Object CircleShape player - SFML CircleShape player object
    */
    sf::Sprite getMySpriteObject();

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
    * @return string token - hashed API Token for Player
    */
    std::string getMyToken();
};