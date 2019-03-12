#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Messages.h"

class Entity
{
public:
	Entity();
	Entity(const std::string& filePath);
	~Entity();

	bool init(const std::string& filePath);

	const float& getMaxHealth() const { return _maxHealth; }
	const float& getHealth() const { return _health; }
	const float& getStrength() const { return _strength; }
	const float& getSpeed() const { return _speed; }
	const std::string& getCharacter() const { return _character; }
	const std::pair<int, int>& getLocation() const { return _location; }
	const std::pair<int, int>& getOldLocation() const { return _oldLocation; }
	const std::string& getReplaceChar() const { return _replaceChar; }

	void displayEntStats();

	void setLocation(std::pair<int, int> location) { _location = location; }
	void setLocation(int x, int y) { _location = std::make_pair(x, y); }
	void setOldLocation(std::pair<int, int> location) { _oldLocation = location; }
	void setOldLocation(int x, int y) { _oldLocation = std::make_pair(x, y); }

	void moveInX(int move) { _oldLocation = _location; _location.first += move; }
	void moveInY(int move) { _oldLocation = _location; _location.second -= move; }

	void update(std::vector<Messages>& messages);
	void attack(std::vector<Messages>& messages, Entity* targetAdress);

private:
	float _maxHealth;
	float _health;
	float _strength;
	float _speed;
	std::string _character;
	std::pair<int, int> _location;
	std::pair<int, int> _oldLocation;
	std::string _replaceChar;

};
