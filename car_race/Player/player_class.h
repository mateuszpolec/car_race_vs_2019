#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>
#include "../Options/options.h"
#include "../JsonWorker/json_worker.h"

/**
* Class Player - handle information about player
* 
*/
class Player : Options, JSONWorker {
    std::string token;
    /* To remember, Vector2f describes data like math cartesian system*/
    sf::Vector2f m_movmentVector;
    sf::Vector2f m_forwardVector = { 0.f, 1.f };
    float m_currentSpeed = 0.f;

    sf::Texture m_playerTexture;
    sf::Sprite m_player; //Generate player object
    sf::Clock clock; // Clock created for elapsing time between frames and correct movement of player 

    /* Handling actual player position and current lap info*/
    int m_currentLap = 1;
    bool m_isNextLap = false;
    std::set<int> checkpointsReached = {};

    /* Handling info about player handbrake */
    bool isHandbrakeOn = false;


    /* Saving information about player movement in current lap - Temporary */
    int actualFrame;
    JSONWorker* jsonWorker;

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

    void getMyRotation();
    /**
    * getMyRotation
    * Function that returns actual player rotation
    * void function, no params
    */

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
    * @return SFML Object Sprite player - SFML Sprite with Texture player object
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
    * recordPlayerMove
    * Temporary function: Saves the movement of player in current lap
    */
    void recordPlayerMove();


    /**
    * moveTostart
    * Function that moves player sprite for starting position
    */
    void moveToStart();
};