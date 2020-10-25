#include "map_worker.h"
#include <iostream>

MapWorker::MapWorker() {
	this->map.load("./Assets/racemap2.tmx");

}

void MapWorker::drawMapOnWindow(sf::RenderWindow *window) {

	const static MapLayer layerZero(this->map, 0); //Made it static, because otherwise the game would constantly load map over and over again
	const static MapLayer layerOne(this->map, 1);
	window->draw(layerZero);
	window->draw(layerOne);
}
