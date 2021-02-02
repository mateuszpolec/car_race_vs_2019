#include "Game.h"

void Game::createWindow() {
	this->m_window = new sf::RenderWindow(sf::VideoMode(s_screenWidth, s_screenHeight), "Car race 1.0.0");
	this->m_window->setFramerateLimit(60); //TODO: Set Framelimit const
}

void Game::render() {

	static MapLayer s_layerZero(this->m_map, 0);
	static MapLayer s_layerOne(this->m_map, 1);

	auto tile_grass_layer = s_layerZero.getTile(this->m_player->getPlayerPositionX(), this->m_player->getPlayerPositionY());
	auto tile_race_track_layer = s_layerOne.getTile(this->m_player->getPlayerPositionX(), this->m_player->getPlayerPositionY());


	this->m_player->checkPlayerCollision(tile_grass_layer.ID);
	this->m_player->checkPlayerCollision(tile_race_track_layer.ID);


	for (Enemy* enemy : this->m_vectorOfEnemies) {
		if (enemy->pointsToFollow.empty()) {
			enemy->createTrack();
		}
		else {
			if(!m_isGameFreezed) {
				auto tile_grass_layer_enemy = s_layerZero.getTile(enemy->getEnemyPositionX(), enemy->getEnemyPositionY());
				enemy->checkEnemyCollision(tile_grass_layer_enemy.ID);
				enemy->moveEnemy();
			}
		}
	}


	// Draw the vertex array
	this->m_window->clear(sf::Color::Black);
	this->m_window->draw(s_layerZero);
	this->m_window->draw(s_layerOne);
	this->m_window->draw(this->m_player->getPlayerSpriteObject());
	this->m_window->draw(this->m_player->showName(this->m_gameFont));
	if (this->m_stateOfGame == 1) {
		this->m_window->draw(this->m_player->showLap(this->m_gameFont, 4));
	}
	else if (this->m_stateOfGame == 2) {
		this->m_window->draw(this->m_player->showLap(this->m_gameFont, 5));
	}
	for (Enemy* enemy : this->m_vectorOfEnemies) {
		this->m_window->draw(enemy->getEnemySpriteObject());
		this->m_window->draw(enemy->showName(this->m_gameFont));
	}


	//Code for first state of game - Qualification Round
	if ( (this->m_isEventActive == false) && (this->m_stateOfGame == 1)) {
		changeStateToQualificationRound();
	}

	// Qualification Round Timer & Text Drawing
	if (this->m_isCountdownActive && this->m_stateOfGame == 1) {
		float timeCountdown = round(this->m_timeCountdown - this->m_globalTimeCounter);
		this->m_window->draw(qualificationLapsText(this->m_gameFont, this->m_player->getPlayerPosition()));
		this->m_window->draw(qualificationLapsHelpText(this->m_gameFont, this->m_player->getPlayerPosition()));
		this->m_window->draw(timeCountdownText(this->m_gameFont, this->m_player->getPlayerPosition(), timeCountdown));
		this->m_isGameFreezed = true;
		if(this->m_timeCountdown - this->m_globalTimeCounter < 0) {
			this->m_isCountdownActive = false;
			this->m_isGameFreezed = false;
		}
	}

	// Qualification Round - Gameplay
	if (this->m_isEventActive && this->m_stateOfGame == 1 && this->m_player->currentLap == 4) {

		int playerPointsCompleted = 450; // Setting the points, that player will make if he end the race.

		std::vector<int> pointsToSort = {};
		std::set<int> startingPlaces = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // How many starting points there are

		for (Enemy* enemy : this->m_vectorOfEnemies) {
			pointsToSort.push_back(enemy->totalPointsCompleted);
		}

		pointsToSort.push_back(playerPointsCompleted);



		while (isThereAnyDuplicates(pointsToSort)) {
			removeDuplicatesFromVector(pointsToSort);
		}

		//Get back to Enemy class and change their completed points to be without any duplicates
		for (short i = 0; i < this->m_vectorOfEnemies.size(); ++i) {
			this->m_vectorOfEnemies[i]->totalPointsCompleted = pointsToSort[i];
		}

		std::sort(pointsToSort.begin(), pointsToSort.end());
		std::reverse(pointsToSort.begin(), pointsToSort.end());

		for (Enemy* enemy : this->m_vectorOfEnemies) {
			std::vector<int>::iterator itr = std::find(pointsToSort.begin(), pointsToSort.end(), enemy->totalPointsCompleted);

			int index = std::distance(pointsToSort.begin(), itr);

			enemy->startingPlace = startingPlacesPoints[index];
			startingPlaces.erase(index);
		}

		int playerStartPosition = *std::next(startingPlaces.begin(), 0);
		this->m_player->startingPlace = startingPlacesPoints[playerStartPosition];

		this->m_isGameFreezed = true;
		this->m_isEventActive = false;
		this->m_stateOfGame = 2;
	}

	//Code for change state to second state of game - Main race round
	if ((this->m_isEventActive == false) && (this->m_stateOfGame == 2)) {
		changeStateToMainRaceRound();
		for (Enemy* enemy : this->m_vectorOfEnemies) {
			enemy->moveToStartPosition();
			enemy->actualPointToGo = 0;
			enemy->halfOfPlot = 0;
			enemy->currentLap = 0;
			enemy->totalPointsCompleted = 0;
		}
		this->m_player->moveToStartPosition();
		this->m_player->checkpointsReached.clear();
		this->m_player->currentLap = 1;
	}

	// Main race round Timer & Text Drawing
	if (this->m_isCountdownActive && this->m_stateOfGame == 2) {
		float timeCountdown = round(this->m_timeCountdown - this->m_globalTimeCounter);
		this->m_window->draw(mainRaceLapsText(this->m_gameFont, this->m_player->getPlayerPosition()));
		this->m_window->draw(mainRaceLapsHelpText(this->m_gameFont, this->m_player->getPlayerPosition()));
		this->m_window->draw(timeCountdownText(this->m_gameFont, this->m_player->getPlayerPosition(), timeCountdown));
		if (this->m_timeCountdown - this->m_globalTimeCounter < 0) {
			this->m_isCountdownActive = false;
			this->m_isGameFreezed = false;
		}
	}
	
	// Main race round Gameplay
	if (this->m_isEventActive && this->m_stateOfGame == 2 && this->m_player->currentLap == 5) {
		int playerPointsCompleted = 100;

		this->m_player->moveToZeroPosition();

		std::vector<int> pointsToSort = {};
		std::set<int> placesInRace = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // What position can you get in race?

		for (Enemy* enemy : this->m_vectorOfEnemies) {
			pointsToSort.push_back(enemy->totalPointsCompleted);
		}

		pointsToSort.push_back(playerPointsCompleted);



		while (isThereAnyDuplicates(pointsToSort)) {
			removeDuplicatesFromVector(pointsToSort);
		}

		//Get back to Enemy class and change their completed points to be without any duplicates
		for (short i = 0; i < this->m_vectorOfEnemies.size(); ++i) {
			this->m_vectorOfEnemies[i]->totalPointsCompleted = pointsToSort[i];
		}

		std::sort(pointsToSort.begin(), pointsToSort.end());
		std::reverse(pointsToSort.begin(), pointsToSort.end());

		for (Enemy* enemy : this->m_vectorOfEnemies) {
			std::vector<int>::iterator itr = std::find(pointsToSort.begin(), pointsToSort.end(), enemy->totalPointsCompleted);

			int index = std::distance(pointsToSort.begin(), itr);
			
			placesInRace.erase(index);

		}

		int playerPlaceInRace = *std::next(placesInRace.begin(), 0);

		this->m_player->placeInRace = playerPlaceInRace + 1;

		this->m_isGameFreezed = true;
		this->m_isEventActive = false;
		this->m_stateOfGame = 3;
	}

	if (this->m_stateOfGame == 3) {
		this->m_window->draw(menuEndBackground());
		this->m_window->draw(menuEndBackground2());
		this->m_window->draw(endRaceText(this->m_gameFont, this->m_player->placeInRace));
		this->m_window->draw(menuEndCup());
		sf::Text playAgain = buttonPlayAgain(this->m_gameFont);
		this->m_window->draw(playAgain);
		sf::IntRect rect(playAgain.getPosition().x, playAgain.getPosition().y, playAgain.getGlobalBounds().width, playAgain.getGlobalBounds().height);
		//if (rect.contains(sf::Mouse::getPosition())) {
		//	std::cout << "True";
		//}
		//else {
		//	std::cout << "False";
		//}
	}





	this->m_window->display();
}


void Game::update() {
	if (!m_isGameFreezed) {
		this->m_player->movePlayer();
	}

	this->m_playercamera->cameraFollowPlayer(*this->m_window, this->m_player->getPlayerPosition());
}


void Game::classInitializer() {
	this->m_api = new APIConnector();
	const std::string token = this->m_api->getAuthToken();
	this->m_player = new Player(token);
	this->m_map.load("./Assets/racemap_new.tmx");
	this->m_playercamera = new PlayerCamera();
	this->m_player->moveToStart();

	for (short i = 0; i < 9; ++i) {
		std::string nameOfEnemy = "Enemy " + std::to_string(i);
		this->m_vectorOfEnemies.push_back(new Enemy(nameOfEnemy));
		this->m_vectorOfEnemies[i]->moveToStart();
	}

	if (this->m_gameFont.loadFromFile("./Assets/RobotoMono-Regular.ttf")) {
		// Error 
	}

}

void Game::eventListener() {

	while (this->m_window->pollEvent(this->m_event)) {
		if (this->m_event.type == sf::Event::Closed)
			this->m_window->close();
	}

	this->m_player->listenPlayerMove();

}

void Game::keepGameAlive() {
	while (this->m_window->isOpen()) {
		this->eventListener();
		this->render();
		this->update();
		sf::Time elapsed1 = m_globalClock.getElapsedTime();
		this->m_globalTimeCounter += elapsed1.asSeconds();
		m_globalClock.restart();
	}
}

void Game::changeStateToMenu() {
	this->m_stateOfGame = 0;
}

void Game::changeStateToQualificationRound() {
	this->m_stateOfGame = 1;
	this->m_isEventActive = true;
	this->m_isCountdownActive = true;
	this->m_timeCountdown = this->m_globalTimeCounter + 10;
}

void Game::changeStateToMainRaceRound() {
	this->m_stateOfGame = 2;
	this->m_isEventActive = true;
	this->m_isCountdownActive = true;
	this->m_timeCountdown = this->m_globalTimeCounter + 10;
}

void Game::changeStateToEndOfRaceScreen() {
	this->m_stateOfGame = 3;
}

Game::Game() {
	this->classInitializer();
	this->createWindow();
}

Game::~Game() {
	delete this->m_window;
}