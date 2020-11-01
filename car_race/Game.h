#include <SFML/Graphics.hpp>
#include "Player/player_class.h"
#include "Player/player_camera.h"
#include "Sockets/api_connector.h"
#include "FileWorker/sfml_layer_loader.h"

class Game {
	private:
		
		sf::RenderWindow* window;
		sf::Event event;

		Player* player;
		APIConnector* api;
		PlayerCamera* playercamera;

		tmx::Map map;

	public:
		/**
		* createWindow
		* Function that creates a SFML window and sets framerate
		*/
		void createWindow();

		/**
		* keepGameAlive
		* SFML while loop for window, updates every state of game
		*/
		void keepGameAlive();

		/**
		* render
		* As the names says, it just draw everything on the window
		*/
		void render();
		/**
		* update
		* Updates every event that needs be updated. For example: player position
		*/
		void update();

		/**
		* eventListener
		* Listens, if any of events happend. For example: Player click any key on keyboard
		*/
		void eventListener();

		/**
		* classInitializer
		* Points every object to it instance
		*/
		void classInitializer();

		Game();
		~Game();
	
};