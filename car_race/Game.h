#include <SFML/Graphics.hpp>
#include "Player/player_class.h"
#include "Player/player_camera.h"
#include "Sockets/api_connector.h"
#include "FileWorker/map_worker.h"
#include "FileWorker/sfml_layer_loader.h"

class Game  {
	private:
		
		sf::RenderWindow* window;
		sf::Event event;

		Player* player;
		APIConnector* api;
		MapWorker* mapworker;
		PlayerCamera* playercamera;

		tmx::Map map;

	public:
		void createWindow();
		void keepGameAlive();
		void render();
		void update();
		void eventListener();
		void classInitializer();
		Game();
		~Game();
	
};