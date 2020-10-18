#include "map_worker.h"

void MapWorker::loadMapFromJson() {
	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(fs::path("../racemap2.json"));
	if (map->getStatus() == tson::ParseStatus::OK) {
		std::cout << "Map is loaded properly!";
	}
}