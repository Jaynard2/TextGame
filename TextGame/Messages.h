#pragma once

class Entity;

struct Messages
{
public:
	Entity* attackerId;
	Entity* target;

};

inline bool operator==(const Messages& rhs, const Messages& lhs)
{
	if (rhs.attackerId == lhs.attackerId && rhs.target == lhs.target)
		return true;

	return false;
}
