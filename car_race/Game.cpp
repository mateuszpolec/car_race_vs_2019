#include "Game.h"
#include <iostream>

void Game::createWindow() {
	this->window = new sf::RenderWindow(sf::VideoMode(1200, 800), "My window");
	this->window->setFramerateLimit(60); //TODO: Set Framelimit const
}

void Game::render() {

	static MapLayer layerZero(this->map, 0);
	static MapLayer layerOne(this->map, 1);

	auto tile_grass_layer = layerZero.getTile(this->player->getMyPositionX(), this->player->getMyPositionY());
	auto tile_race_track_layer = layerOne.getTile(this->player->getMyPositionX(), this->player->getMyPositionY());

	this->player->checkPlayerCollision(tile_grass_layer.ID);



	this->window->clear(sf::Color::Black);
	this->window->draw(layerZero);
	this->window->draw(layerOne);
	this->window->draw(this->player->getMySpriteObject());
	this->window->display();
}


void Game::update() {
	this->player->movePlayer();
	this->playercamera->cameraFollowPlayer(*this->window, this->player->getMyPosition());
}


void Game::classInitializer() {
	this->api = new APIConnector();
	const std::string token = this->api->getAuthToken();
	this->player = new Player(token);
	this->map.load("./Assets/testmap.tmx");
	this->playercamera = new PlayerCamera();
	this->player->moveToStart();
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