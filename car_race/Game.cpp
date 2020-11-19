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

	// Create a vertex array for drawing; a line strip is perfect for this
	sf::VertexArray vertices(sf::LinesStrip, 0);

	std::vector<std::vector<sf::Vector2f>> vectorOfPoints;
	// Calculate the points on the curve (10 segments)
	std::vector<sf::Vector2f> firstEnemyFirstPoints =
		CalcCubicBezier(
			sf::Vector2f(250, 600),
			sf::Vector2f(620, 125),
			sf::Vector2f(100, 100),
			sf::Vector2f(620, 125),
			25);

	std::vector<sf::Vector2f> fisrtEnemySecondPoints =
		CalcCubicBezier(
			sf::Vector2f(620, 125),
			sf::Vector2f(1050, 435),
			sf::Vector2f(1060, 175),
			sf::Vector2f(1050, 435),
			25);

	std::vector<sf::Vector2f> firstEnemyThirdPoints =
		CalcCubicBezier(
			sf::Vector2f(1050, 435),
			sf::Vector2f(750, 950),
			sf::Vector2f(1100, 850),
			sf::Vector2f(750, 950),
			25
		);

	std::vector<sf::Vector2f> firstEnemyFourthPoints =
		CalcCubicBezier(
			sf::Vector2f(750, 950),
			sf::Vector2f(250, 600),
			sf::Vector2f(300, 1050),
			sf::Vector2f(250, 600),
			25
		);

	vectorOfPoints.push_back(firstEnemyFirstPoints);
	vectorOfPoints.push_back(fisrtEnemySecondPoints);
	vectorOfPoints.push_back(firstEnemyThirdPoints);
	vectorOfPoints.push_back(firstEnemyFourthPoints);

	// Append the points as vertices to the vertex array
	for (int i = 0; i < vectorOfPoints.size(); ++i) {
		for (std::vector<sf::Vector2f>::const_iterator a = vectorOfPoints[i].begin(); a != vectorOfPoints[i].end(); ++a) {
			vertices.append(sf::Vertex(*a, sf::Color::White));
		}
	}
	// ...

	// Draw the vertex array
	this->window->clear(sf::Color::Black);
	this->window->draw(layerZero);
	this->window->draw(layerOne);
	this->window->draw(vertices);
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
	std::cout << this->player->getPlayerPosition().x << " " << this->player->getPlayerPosition().y << std::endl;
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