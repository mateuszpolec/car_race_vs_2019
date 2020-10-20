#include "sfml_layer_loader.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/detail/Log.hpp>
#include <SFML/Graphics.hpp>

class MapWorker {


public:

	
	tmx::Map map;

	/**
	* Constrcutor
	* Loads the map from tmx file
	*/
	MapWorker();

	/**
	* drawMapOnWindow
	* Drawing the map on window
	* @param SFML Object RenderWindow - reference to the main window
	*/
	void drawMapOnWindow(sf::RenderWindow & window);
};