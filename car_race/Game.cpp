#include "Game.h"
#include <iostream>

void Game::createWindow() {
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "My window");
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
			enemy->moveEnemy();
			enemy->checkEnemyCollision(tile_grass_layer.ID);
		}
	}
	// Draw the vertex array
	this->window->clear(sf::Color::Black);
	this->window->draw(s_layerZero);
	this->window->draw(s_layerOne);
	this->window->draw(this->player->getPlayerSpriteObject());
	for (Enemy* enemy : this->vectorOfEnemies) {
		this->window->draw(enemy->getEnemySpriteObject());
	}
	this->window->display();
}


void Game::update() {
	this->player->movePlayer();
	this->playercamera->cameraFollowPlayer(*this->window, this->player->getPlayerPosition());

	//std::cout << this->player->getPlayerPosition().x << " " << this->player->getPlayerPosition().y << std::endl;
}


void Game::classInitializer() {
	this->api = new APIConnector();
	const std::string token = this->api->getAuthToken();
	this->player = new Player(token);
	this->map.load("./Assets/testmap.tmx");
	this->playercamera = new PlayerCamera();
	this->player->moveToStart();

	for (short i = 0; i < 10; ++i) {
		std::string nameOfEnemy = "Enemy " + std::to_string(i);
		this->vectorOfEnemies.push_back(new Enemy(nameOfEnemy));
		this->vectorOfEnemies[i]->moveToStart();
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
	}
}

Game::Game() {
	this->classInitializer();
	this->createWindow();
}

Game::~Game() {
	delete this->window;
}