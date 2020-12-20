#include "Game.h"

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


	//Code for first state of game - Qualification Round
	if ( (this->isEventActive == false) && (this->stateOfGame == 1)) {
		changeStateToQualificationRound();
	}

	if (this->isCountdownActive && this->stateOfGame == 1) {
		std::string timeCountdown = std::to_string(round(this->timeCountdown - this->globalTimeCounter));
		this->window->draw(qualificationLapsText(this->gameFont, this->player->getPlayerPosition()));
		this->window->draw(qualificationLapsHelpText(this->gameFont, this->player->getPlayerPosition()));
		this->window->draw(timeCountdownText(this->gameFont, this->player->getPlayerPosition(), timeCountdown));
		this->isGameFreezed = true;
		if(this->timeCountdown - this->globalTimeCounter < 0) {
			this->isCountdownActive = false;
			this->isGameFreezed = false;
		}
	}

	if (this->isEventActive && this->stateOfGame == 1 && this->player->currentLap == 4) {

		int playerPointsCompleted = 450; // Setting the points, that player will make if he end the race.

		std::vector<int> pointsToSort = { playerPointsCompleted };


		for (Enemy* enemy : this->vectorOfEnemies) {
			pointsToSort.push_back(enemy->totalPointsCompleted);
		}

		std::sort(pointsToSort.begin(), pointsToSort.end());
		std::reverse(pointsToSort.begin(), pointsToSort.end());


		while (isThereAnyDuplicates(pointsToSort)) {
			removeDuplicatesFromVector(pointsToSort);
		}

		for (Enemy* enemy : this->vectorOfEnemies) {
			std::vector<int>::iterator itr = std::find(pointsToSort.begin(), pointsToSort.end(), enemy->totalPointsCompleted);

			int index = std::distance(pointsToSort.begin(), itr);

			//std::cout << "Enemy " << enemy->m_Name << " will start at place " << pointsToSort[index] << "\n";
		}


		for (auto& point : pointsToSort) {
			std::cout << point << "\n";
		}



		this->isGameFreezed = true;

	}

	this->window->display();
}


void Game::update() {
	if (!isGameFreezed) {
		this->player->movePlayer();
	}

	this->playercamera->cameraFollowPlayer(*this->window, this->player->getPlayerPosition());
}


void Game::classInitializer() {
	this->api = new APIConnector();
	const std::string token = this->api->getAuthToken();
	this->player = new Player(token);
	this->map.load("./Assets/racemap_new.tmx");
	this->playercamera = new PlayerCamera();
	this->player->moveToStart();

	for (short i = 0; i < 9; ++i) {
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
	this->stateOfGame = 0;
}

void Game::changeStateToQualificationRound() {
	this->stateOfGame = 1;
	this->window->draw(qualificationLapsText(this->gameFont, this->player->getPlayerPosition()));
	this->window->draw(qualificationLapsHelpText(this->gameFont, this->player->getPlayerPosition()));
	this->isEventActive = true;
	this->isCountdownActive = true;
	this->timeCountdown = this->globalTimeCounter + 10;
}

void Game::changeStateToMainRaceRound() {
	this->stateOfGame = 2;
}

void Game::changeStateToEndOfRaceScreen() {
	this->stateOfGame = 3;
}

Game::Game() {
	this->classInitializer();
	this->createWindow();
}

Game::~Game() {
	delete this->window;
}