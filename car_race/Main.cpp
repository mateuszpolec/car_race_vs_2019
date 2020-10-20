
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Player/player_class.h"
#include "Sockets/api_connector.h"
#include "FileWorker/sfml_layer_loader.h"
#include "FileWorker/map_worker.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");

    APIConnector api;
    MapWorker mapworker;
    sf::View followPlayer;


    const std::string token = api.getAuthToken();

    Player player(token);
    followPlayer.setSize(1200.f, 800.f);

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
        window.setView(followPlayer);
        followPlayer.setCenter(player.getMyPosition());
        player.movePlayer();
        window.display();
    }

    return 0;
}