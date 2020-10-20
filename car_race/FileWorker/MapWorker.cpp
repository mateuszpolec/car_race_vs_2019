#include "map_worker.h"
#include <iostream>

MapWorker::MapWorker() {
	this->map.load("./Assets/racemap2.tmx");

}

void MapWorker::drawMapOnWindow(sf::RenderWindow & window) {

	const static MapLayer layerZero(this->map, 0);
	const static MapLayer layerOne(this->map, 1);
	window.draw(layerZero);
	window.draw(layerOne);
}

//void MapWorker::drawMapOnWindowTest(sf::RenderWindow& window, MapLayer& layer) {
//	window.draw(layer);
//}
//
//MapLayer MapWorker::getLayerZero() {
//	return m_layerZero;
//}