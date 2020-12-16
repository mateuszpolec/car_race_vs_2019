#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player/player_class.h"
#include "Player/player_camera.h"
#include "Sockets/api_connector.h"
#include "FileWorker/sfml_layer_loader.h"
#include "Enemy/enemy.h"
#include "FileWorker/RouteCreator.h"
#include "./Options/TextManager.h"

class Game {

private:
	sf::RenderWindow* window;
	sf::Event event;

	Player* player;
	APIConnector* api;
	PlayerCamera* playercamera;

	// Handling Time in Game
	sf::Clock globalClock;
	float globalTimeCounter;
	bool isGameFreezed = true;


	//Vector pointing at instances of Enemy classes
	std::vector<Enemy*> vectorOfEnemies = {};

	tmx::Map map;
	int lapsToComplete = 3;

	// Handling text in game
	sf::Font gameFont;

	// Handling the state of game
	/**
	* stateOfGame = 0 -> Player in menu section
	* stateOfGame = 1 -> Player in qualification round
	* stateOfGame = 2 -> Player in main race round
	* stateOfGame = 3 -> Player in end screen round
	*/

	struct gameState {
		int stateOfGame = 1;
		int timeCountdown = 0;
		bool isEventActive = false;
		bool isCountdownActive = false;
		int nextState = 2;
	};

	gameState* gameStateInstance;

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

	void changeStateToMenu();
	void changeStateToQualificationRound();
	void changeStateToMainRaceRound();
	void changeStateToEndOfRaceScreen();

	Game();
	~Game();
	
};

#endif