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
	this->player->checkPlayerCollision(tile_race_track_layer.ID);


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

	// Qualification Round Timer & Text Drawing
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

	// Qualification Round - Gameplay
	if (this->isEventActive && this->stateOfGame == 1 && this->player->currentLap == 4) {

		int playerPointsCompleted = 450; // Setting the points, that player will make if he end the race.

		std::vector<int> pointsToSort = {};
		std::set<int> startingPlaces = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // How many starting points there are

		for (Enemy* enemy : this->vectorOfEnemies) {
			pointsToSort.push_back(enemy->totalPointsCompleted);
		}

		pointsToSort.push_back(playerPointsCompleted);



		while (isThereAnyDuplicates(pointsToSort)) {
			removeDuplicatesFromVector(pointsToSort);
		}

		//Get back to Enemy class and change their completed points to be without any duplicates
		for (short i = 0; i < this->vectorOfEnemies.size(); ++i) {
			this->vectorOfEnemies[i]->totalPointsCompleted = pointsToSort[i];
		}

		std::sort(pointsToSort.begin(), pointsToSort.end());
		std::reverse(pointsToSort.begin(), pointsToSort.end());

		for (Enemy* enemy : this->vectorOfEnemies) {
			std::vector<int>::iterator itr = std::find(pointsToSort.begin(), pointsToSort.end(), enemy->totalPointsCompleted);

			int index = std::distance(pointsToSort.begin(), itr);

			enemy->startingPlace = startingPlacesPoints[index];
			startingPlaces.erase(index);
		}

		int playerStartPosition = *std::next(startingPlaces.begin(), 0);
		this->player->startingPlace = startingPlacesPoints[playerStartPosition];

		this->isGameFreezed = true;
		this->isEventActive = false;
		this->stateOfGame = 2;
	}

	//Code for change state to second state of game - Main race round
	if ((this->isEventActive == false) && (this->stateOfGame == 2)) {
		changeStateToMainRaceRound();
		for (Enemy* enemy : this->vectorOfEnemies) {
			enemy->moveToStartPosition();
			enemy->actualPointToGo = 0;
			enemy->halfOfPlot = 0;
		}
		this->player->moveToStartPosition();
	}

	// Main race round Timer & Text Drawing
	if (this->isCountdownActive && this->stateOfGame == 2) {
		std::string timeCountdown = std::to_string(round(this->timeCountdown - this->globalTimeCounter));
		this->window->draw(mainRaceLapsText(this->gameFont, this->player->getPlayerPosition()));
		this->window->draw(mainRaceLapsHelpText(this->gameFont, this->player->getPlayerPosition()));
		this->window->draw(timeCountdownText(this->gameFont, this->player->getPlayerPosition(), timeCountdown));
		if (this->timeCountdown - this->globalTimeCounter < 0) {
			this->isCountdownActive = false;
			this->isGameFreezed = false;
		}
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
	this->isEventActive = true;
	this->isCountdownActive = true;
	this->timeCountdown = this->globalTimeCounter + 10;
}

void Game::changeStateToMainRaceRound() {
	this->stateOfGame = 2;
	this->isEventActive = true;
	this->isCountdownActive = true;
	this->timeCountdown = this->globalTimeCounter + 10;
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