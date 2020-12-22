#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Player/PlayerCamera.h"
#include "Sockets/ApiConnector.h"
#include "FileWorker/sfml_layer_loader.h"
#include "Enemy/enemy.h"
#include "FileWorker/RouteCreator.h"
#include "./Options/TextManager.h"
#include <iostream>
#include <algorithm>


class Game {

private:
	sf::RenderWindow* m_window;
	sf::Event m_event;

	Player* m_player;
	APIConnector* m_api;
	PlayerCamera* m_playercamera;

	// Handling Time in Game
	sf::Clock m_globalClock;
	float m_globalTimeCounter;
	bool m_isGameFreezed = true;


	//Vector pointing at instances of Enemy classes
	std::vector<Enemy*> m_vectorOfEnemies = {};

	tmx::Map m_map;

	// Handling text in game
	sf::Font m_gameFont;

	// Handling the state of game
	/**
	* stateOfGame = 0 -> Player in menu section
	* stateOfGame = 1 -> Player in qualification round
	* stateOfGame = 2 -> Player in main race round
	* stateOfGame = 3 -> Player in end screen round
	*/

	int m_stateOfGame = 1;
	int m_timeCountdown = 0;
	bool m_isEventActive = false;
	bool m_isCountdownActive = false;
	int m_nextState = 2;

public:

	Game();
	~Game();

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

	// TODO: Documentation
	void changeStateToMenu();

	//TODO: Documentation
	void changeStateToQualificationRound();

	//TODO: Documentation
	void changeStateToMainRaceRound();

	//TODO: Documentation
	void changeStateToEndOfRaceScreen();
	
};

#endif