#pragma once
#include <vector>
#include <unordered_set>
#include <random>
#include "common.h"
#include "Entity.h"

class Grid {
public:

	//Entities are referenced through IDs
	typedef i32 EntityID;

	//must beable to insert entity into grid
	virtual EntityID insert(Entity e) = 0;

	//time step simulation
	virtual void update(std::mt19937 &rng) = 0;
	
	//clear simulation data
	virtual void clear() = 0;

	virtual f32 getMin() const = 0;
	virtual f32 getMax() const = 0;


	const std::vector<Entity> &getEntities() const;
	const std::unordered_set<EntityID> &getS() const;
	const std::unordered_set<EntityID> &getI() const;
	const std::unordered_set<EntityID> &getR() const;


protected:

	//list of all entities in system
	std::vector<Entity> entities;

	//hash map of all entities who are susceptible
	std::unordered_set<EntityID> S;
	//hash map of all entities who are infected
	std::unordered_set<EntityID> I;
	//hash map of all entities who are removed
	std::unordered_set<EntityID> R;
};

