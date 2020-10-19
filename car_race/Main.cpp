
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Player/player_class.h"
#include "Sockets/api_connector.h"
#include "FileWorker/sfml_layer_loader.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");

    APIConnector api;
    sf::View followPlayer;
    tmx::Map map;
    map.load("./Assets/racemap2.tmx");
    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);

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
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(player.getMySpriteObject());
        window.setView(followPlayer);
        followPlayer.setCenter(player.getMyPosition());
        player.movePlayer();
        window.display();
    }

    return 0;
}