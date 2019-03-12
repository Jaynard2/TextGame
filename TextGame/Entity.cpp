#include "Entity.h"
#include "FileReader.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Entity::Entity() : _maxHealth(NULL), _health(NULL), _strength(NULL), _speed(NULL)
{
}

Entity::Entity(const std::string & filePath) : _maxHealth(NULL), _health(NULL), _strength(NULL), _speed(NULL)
{
	init(filePath);
}


Entity::~Entity()
{
}

bool Entity::init(const std::string & filePath)
{
	std::string characterInfo;
	if (!fileReader.readFileToLower(filePath, characterInfo))
	{
		std::cout << "Error loading entity file\n";
		return false;
	}

	std::stringstream stringStream;
	int statLocation;
	std::string stat;

	//Get health
	statLocation = characterInfo.find("health: ");

	if (statLocation == -1)
	{
		std::cout << "Cannot find health in " + filePath << std::endl;
		return false;
	}

	statLocation += 7;
	stat = characterInfo.substr(statLocation, 4);
	stringStream << stat;
	stringStream >> _maxHealth;
	_health = _maxHealth;

	stringStream.clear();

	//Get strength
	statLocation = characterInfo.find("strength: ");

	if (statLocation == -1)
	{
		std::cout << "cannot find strength in " + filePath << std::endl;
		return false;
	}

	statLocation += 9;
	stat = characterInfo.substr(statLocation, 3);
	stringStream << stat;
	stringStream >> _strength;

	stringStream.clear();

	//Get speed
	statLocation = characterInfo.find("speed: ");

	if (statLocation == -1)
	{
		std::cout << "Cannot find speed in " + filePath << std::endl;
		return false;
	}

	statLocation += 6;
	stat = characterInfo.substr(statLocation, 3);
	stringStream << stat;
	stringStream >> _speed;

	stringStream.clear();

	//Get character
	statLocation = characterInfo.find("character: ");

	if (statLocation == -1)
	{
		std::cout << "cannot find character in " + filePath << std::endl;
		return false;
	}

	statLocation += 10;
	stat = characterInfo.substr(statLocation, 2);
	stringStream << stat;
	stringStream >> _character;

	stringStream.clear();

	//Get replacement char
	statLocation = characterInfo.find("rcharacter: ");

	if (statLocation == -1)
	{
		std::cout << "cannot find rcharacter in " + filePath << std::endl;
		return false;
	}

	statLocation += 11;
	stat = characterInfo.substr(statLocation, 2);
	stringStream << stat;
	stringStream >> _replaceChar;

	stringStream.clear();

	return true;
}

void Entity::displayEntStats()
{
	std::cout << "Health: " << _health << "/" << _maxHealth;

}

void Entity::update(std::vector<Messages>& messages)
{
	for (int i = 0; i < messages.size(); ++i)
	{
		if (messages[i].target == this)
		{
			_health -= messages[i].attackerId->getStrength();
			messages.erase(std::remove(messages.begin(), messages.end(), messages[i]), messages.end());
		}
	}
}

void Entity::attack(std::vector<Messages>& messages, Entity* targetAdress)
{
	Messages message;

	message.attackerId = this;
	message.target = targetAdress;

	messages.push_back(message);
}
