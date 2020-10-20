
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Player/player_class.h"
#include "Sockets/api_connector.h"
#include "FileWorker/sfml_layer_loader.h"
#include "FileWorker/map_worker.h"
#include "Player/player_camera.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");


    //Load all classes that works with enviroment
    APIConnector api;
    MapWorker mapworker;


    const std::string token = api.getAuthToken();

    //Load all classes that works with player
    Player player(token);
    PlayerCamera playercamera;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
 
        player.listenPlayerMove();
        mapworker.drawMapOnWindow(window);
        window.draw(player.getMySpriteObject());
        playercamera.cameraFollowPlayer(window, player.getMyPosition());
        player.movePlayer();
        player.getMyVelocity();
        window.display();
    }

    return 0;
}