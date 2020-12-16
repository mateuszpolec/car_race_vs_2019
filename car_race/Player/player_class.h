#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"
#include "../JsonWorker/json_worker.h"

/**
* Class Player - handle information about player
* 
*/
class Player : JSONWorker {
    std::string m_token;
    /* To remember, Vector2f describes data like math cartesian system*/
    sf::Vector2f movementVector;
    sf::Vector2f forwardVector = { 0.f, 1.f };
    float currentSpeed = 0.f;

    sf::Texture playerTexture;
    sf::Sprite player; //Generate player object
    sf::Clock clock; // Clock created for elapsing time between frames and correct movement of player 

    /* Handling actual player position and current lap info*/
    int currentLap = 0;
    bool isNextLap = false;
    std::set<int> checkpointsReached = {};
    float timeCounter;

    /* Handling info about player handbrake */
    bool isHandbrakeOn = false;


    /* Saving information about player movement in current lap - Temporary */
    JSONWorker* jsonWorker;

 public:
    /**
    * Constructor
    * @param string authtoken - Authentication token for API communication
    */

     Player(std::string authtoken);


     /**
    * getMyRotation
    * Function that returns actual player rotation
    * void function, no params
    */
    void getMyRotation();

    /**
    * getMyPosition
    * Function that returns player position
    * @return - SFML Object Vector2f with player position on map
    */
    sf::Vector2f getPlayerPosition();


    /**
    * getPlayerPositionX
    * Function that returns player position in X axis including size of tile
    * @return ABS int value with player position in X axis
    */
    int getPlayerPositionX();


    /**
    * getPlayerPositionY
    * Function that returns player position in Y axis including size of tile
    * @return ABS int value with player position in Y axis
    */
    int getPlayerPositionY();

    /**
    * getPlayerSpriteObject
    * Function returns player sprite object, like shape, color
    * @param -
    * @return SFML Object Sprite player - SFML Sprite with Texture player object
    */
    sf::Sprite getPlayerSpriteObject();

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
    * checkPlayerCollision
    * To be more precise, the function checks on what tile is player "standing" on in this specific moment and starts event
    * for the given tile. For example, if it's grass the method will slow down the player.
    * @param uint32_t tileID
    */
    void checkPlayerCollision(std::uint32_t tileID);

    /**
    * getMyToken
    * Function that returns auth token for API
    * @return string token - hashed API Token for Player
    */
    std::string getMyToken();

    /**
    * moveTostart
    * Function that moves player sprite for starting position
    */
    void moveToStart();


    /**
    * showName
    * Function that display player name on the map just a little above player sprite
    * @param sf::Font gameFont - Reference to font variable
    * @return sf::Text text - Player name with font, size, and all needed attributes
    */
    sf::Text showName(sf::Font& gameFont);
};

#endif