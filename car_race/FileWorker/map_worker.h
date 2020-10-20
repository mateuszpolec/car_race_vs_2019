#include "sfml_layer_loader.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/detail/Log.hpp>
#include <SFML/Graphics.hpp>

class MapWorker {


public:


	tmx::Map map;

	MapWorker();

	void drawMapOnWindow(sf::RenderWindow & window);
};