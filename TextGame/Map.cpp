#include "Map.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include "FileReader.h"

Map::Map()
{
}

Map::Map(const std::string& filePath, std::vector<Entity>& entities)
{
	init(filePath, entities);
}


Map::~Map()
{
}

bool Map::init(const std::string & filePath, std::vector<Entity>& entities)
{
	fileReader.readFile(filePath, _map);

	_width = _map.find("\n") + 1;

	for (int i = 0; i < entities.size(); ++i)
	{
		int playerPos = _map.find(entities[i].getReplaceChar());
		entities[i].setLocation(makeIntoCoords(playerPos));
		entities[i].setOldLocation(makeIntoCoords(playerPos));
		_map.replace(playerPos, 1, entities[i].getCharacter());
	}

	std::cout << _map;

	return true;
}

void Map::update(std::vector<Entity>& entities)
{
	bool moveEnt = true;

	for (int i = 0; i < entities.size(); ++i)
	{

		int oldPos = convertIntoInt(entities[i].getOldLocation());

		if (_map[convertIntoInt(entities[i].getLocation())] == '#')
		{
			moveEnt = false;
		}

		int x = 0;
		while ( x < entities.size())
		{
			if (x == i)
				++x;

			if (x >= entities.size())
				break;

			if (entities[i].getLocation() == entities[x].getLocation() && entities[x].getHealth() > 0)
			{
				moveEnt = false;
				break;
			}
			++x;
		}

		if (moveEnt)
		{
			_map.replace(oldPos, 1, " ");
			_map.replace(convertIntoInt(entities[i].getLocation()), 1, entities[i].getCharacter());
		}
		else
		{
			entities[i].setLocation(makeIntoCoords(oldPos));
		}

		if (entities[i].getHealth() <= 0)
			_map.replace(convertIntoInt(entities[i].getLocation()), 1, " ");

	}
}

std::pair<int, int> Map::makeIntoCoords(int location)
{
	int x = location % _width;
	int y = location / _width;

	return std::make_pair(x, y);
}

int Map::convertIntoInt(std::pair<int, int> location)
{
	int pos = (location.second) * _width;
    pos += location.first;

	return pos;
}

void Map::draw()
{
	std::cout << _map;
}
