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

	short i = 0;

	Enemy* testEnemy = this->vectorOfEnemies[0];


	std::cout << "What's in front of enemy zero: ";

	for (int x_left = testEnemy->getEnemyPositionX(); x_left < testEnemy->getEnemyPositionX() + 10; ++x_left) {
		std::cout << layerZero.getTile(x_left, testEnemy->getEnemyPositionX()).ID << " ";
	}

	for (int y_up = testEnemy->getEnemyPositionY(); y_up < testEnemy->getEnemyPositionY() + 10; ++y_up) {
		std::cout << layerZero.getTile(y_up, testEnemy->getEnemyPositionX()).ID << " ";
	}

	for (int x_right = testEnemy->getEnemyPositionX(); x_right < testEnemy->getEnemyPositionY() - 10; --x_right) {
		std::cout << layerZero.getTile(x_right, testEnemy->getEnemyPositionX()).ID << " ";
	}

	std::cout << std::endl;



	//for (Enemy* enemy : this->vectorOfEnemies) {
	//	i++;
	//	std::cout << "Enemy " << i << ": " << std::endl;
	//	for (int i = enemy->getEnemyPositionX(); i < enemy->getEnemyPositionX() + 10; ++i) {
	//		std::cout << layerZero.getTile(i, enemy->getEnemyPositionY()).ID << " ";
	//	}

	//	std::cout << std::endl;

	//	for (int j = enemy->getEnemyPositionY(); j < enemy->getEnemyPositionY() + 10; ++j) {
	//		std::cout << layerZero.getTile(enemy->getEnemyPositionX(), i).ID << " ";
	//	}


	//	std::cout << std::endl;
	//}


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

	std::cout << "Player position: " << this->player->getPlayerPosition().x << " " << this->player->getPlayerPosition().y << std::endl;
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