#pragma once
#include <vector>
#include <unordered_set>
#include <random>
#include "common.h"
#include "Entity.h"

class Grid {
public:
	typedef i32 EntityID;

	virtual EntityID insert(Entity e) = 0;
	virtual void update(std::mt19937 &rng) = 0;
	virtual void clear() = 0;

	const std::vector<Entity> &getEntities() const;
	const std::unordered_set<EntityID> &getS() const;
	const std::unordered_set<EntityID> &getI() const;
	const std::unordered_set<EntityID> &getR() const;

protected:
	std::vector<Entity> entities;
	std::unordered_set<EntityID> S;
	std::unordered_set<EntityID> I;
	std::unordered_set<EntityID> R;
};

