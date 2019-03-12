#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include <utility>

class Map
{
public:
	Map();
	Map(const std::string& filePath, std::vector<Entity>& entities); //First entity must be the player
	~Map();

	bool init(const std::string& filePath, std::vector<Entity>& entities);

	void update(std::vector<Entity>& entities);

	const std::string& getMap() const { return _map; }

	std::pair<int, int> makeIntoCoords(int location);
	int convertIntoInt(std::pair<int, int> location);

	void draw();

private:
	std::string _map;
	int _width;

};

