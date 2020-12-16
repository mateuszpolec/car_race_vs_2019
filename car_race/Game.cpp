#include "Game.h"
#include <iostream>

void Game::createWindow() {
	this->window = new sf::RenderWindow(sf::VideoMode(s_screenHeight, s_screenWidth), "My window");
	this->window->setFramerateLimit(60); //TODO: Set Framelimit const
}

void Game::render() {

	static MapLayer s_layerZero(this->map, 0);
	static MapLayer s_layerOne(this->map, 1);

	auto tile_grass_layer = s_layerZero.getTile(this->player->getPlayerPositionX(), this->player->getPlayerPositionY());
	auto tile_race_track_layer = s_layerOne.getTile(this->player->getPlayerPositionX(), this->player->getPlayerPositionY());


	this->player->checkPlayerCollision(tile_grass_layer.ID);


	for (Enemy* enemy : this->vectorOfEnemies) {
		if (enemy->pointsToFollow.empty()) {
			enemy->createTrack();
		}
		else {
			if(!isGameFreezed) {
				auto tile_grass_layer_enemy = s_layerZero.getTile(enemy->getEnemyPositionX(), enemy->getEnemyPositionY());
				enemy->checkEnemyCollision(tile_grass_layer_enemy.ID);
				enemy->moveEnemy();
			}
		}
	}


	// Draw the vertex array
	this->window->clear(sf::Color::Black);
	this->window->draw(s_layerZero);
	this->window->draw(s_layerOne);
	this->window->draw(this->player->getPlayerSpriteObject());
	this->window->draw(this->player->showName(this->gameFont));
	for (Enemy* enemy : this->vectorOfEnemies) {
		this->window->draw(enemy->getEnemySpriteObject());
		this->window->draw(enemy->showName(this->gameFont));
	}

	if (gameStateInstance->isEventActive == false) {

	}


	this->window->display();
}


void Game::update() {
	if (!isGameFreezed) {
		this->player->movePlayer();
	}
	this->playercamera->cameraFollowPlayer(*this->window, this->player->getPlayerPosition());
	 
	if (this->globalTimeCounter > 10) {
		isGameFreezed = false;
	}
}


void Game::classInitializer() {
	this->api = new APIConnector();
	const std::string token = this->api->getAuthToken();
	this->player = new Player(token);
	this->map.load("./Assets/racemap_new.tmx");
	this->playercamera = new PlayerCamera();
	this->player->moveToStart();

	for (short i = 0; i < 10; ++i) {
		std::string nameOfEnemy = "Enemy " + std::to_string(i);
		this->vectorOfEnemies.push_back(new Enemy(nameOfEnemy));
		this->vectorOfEnemies[i]->moveToStart();
	}

	if (this->gameFont.loadFromFile("./Assets/RobotoMono-Regular.ttf")) {
		// Error 
	}

}

void Game::eventListener() {

	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}

	this->player->listenPlayerMove();

}

void Game::keepGameAlive() {
	while (this->window->isOpen()) {
		this->eventListener();
		this->render();
		this->update();
		sf::Time elapsed1 = globalClock.getElapsedTime();
		this->globalTimeCounter += elapsed1.asSeconds();
		globalClock.restart();
	}
}

void Game::changeStateToMenu() {
	gameStateInstance->stateOfGame = 0;
}

void Game::changeStateToQualificationRound() {
	gameStateInstance->stateOfGame = 1;
	this->window->draw(qualificationLapsText(this->gameFont, this->player->getPlayerPosition()));
	this->window->draw(qualificationLapsHelpText(this->gameFont, this->player->getPlayerPosition()));
	gameStateInstance->timeCountdown = 10;
}

void Game::changeStateToMainRaceRound() {
	gameStateInstance->stateOfGame = 2;
}

void Game::changeStateToEndOfRaceScreen() {
	gameStateInstance->stateOfGame = 3;
}

Game::Game() {
	this->classInitializer();
	this->createWindow();
}

Game::~Game() {
	delete this->window;
}