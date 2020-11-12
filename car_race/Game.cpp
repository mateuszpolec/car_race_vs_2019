#include "Game.h"
#include <iostream>

void Game::createWindow() {
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "My window");
	this->window->setFramerateLimit(60); //TODO: Set Framelimit const
}

void Game::render() {

	static MapLayer layerZero(this->map, 0);
	static MapLayer layerOne(this->map, 1);

	auto tile_grass_layer = layerZero.getTile(this->player->getPlayerPositionX(), this->player->getPlayerPositionY());
	auto tile_race_track_layer = layerOne.getTile(this->player->getPlayerPositionX(), this->player->getPlayerPositionY());

	this->player->checkPlayerCollision(tile_grass_layer.ID);

	Enemy* testEnemy = this->vectorOfEnemies[0];


	std::vector<int> leftSideTiles = {};
	std::vector<int> upSideTiles = {};
	std::vector<int> rightSideTiles = {};

	// Append tiles from left side of player to vector
	for (int x_left = testEnemy->getEnemyPositionX(); x_left < testEnemy->getEnemyPositionX() + 10; ++x_left) {
		leftSideTiles.push_back(layerZero.getTile(x_left, testEnemy->getEnemyPositionY()).ID);
	}

	// Append tiles from up side of player to vector
	for (int y_up = testEnemy->getEnemyPositionY(); y_up < testEnemy->getEnemyPositionY() + 10; ++y_up) {
		upSideTiles.push_back(layerZero.getTile(testEnemy->getEnemyPositionX(), y_up).ID);
	}

	// Append tiles from right side of player to vector
	for (int x_right = testEnemy->getEnemyPositionX(); x_right > testEnemy->getEnemyPositionX() - 10; --x_right) {
		rightSideTiles.push_back(layerZero.getTile(x_right, testEnemy->getEnemyPositionY()).ID);
	}

	testEnemy->checkSurronding(leftSideTiles, upSideTiles, rightSideTiles);
	testEnemy->moveEnemy();



	this->window->clear(sf::Color::Black);
	this->window->draw(layerZero);
	this->window->draw(layerOne);
	this->window->draw(this->player->getPlayerSpriteObject());
	for (Enemy* enemy : this->vectorOfEnemies) {
		this->window->draw(enemy->getEnemySpriteObject());
	}
	this->window->display();
}


void Game::update() {
	this->player->movePlayer();
	this->playercamera->cameraFollowPlayer(*this->window, this->player->getPlayerPosition());
	for (auto enemy : this->vectorOfEnemies) {
		enemy->checkPossibleMove();
	}
}


void Game::classInitializer() {
	this->api = new APIConnector();
	const std::string token = this->api->getAuthToken();
	this->player = new Player(token);
	this->map.load("./Assets/testmap.tmx");
	this->playercamera = new PlayerCamera();
	this->player->moveToStart();

	for (short i = 0; i < 10; ++i) {
		this->vectorOfEnemies.push_back(new Enemy());
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