#pragma once
#include <array>
#include <vector>
#include <unordered_set>
#include <stdio.h>

#include "Grid.h"
#include "Util.h"
#include <random>

class Grid2D : public Grid{

public:

	EntityID insert(Entity e) override;
	void update(std::mt19937 &rng);
	void clear();
	
	f32 getMin() const override;
	f32 getMax() const override;
	
	static constexpr float MAX = NUM_GRIDS;
	static constexpr float MIN = 0;
protected:
	std::unordered_set<EntityID> new_I;
	std::unordered_set<EntityID> new_R;
	std::array<std::unordered_set<EntityID>, NUM_GRIDS*NUM_GRIDS> grid;
	
	virtual void setEntitiesTargetVel(std::mt19937 &rng);
	glm::i32vec2 getQuad(const glm::vec2 &pos);
	std::unordered_set<EntityID> &getSet(int c, int r);
	std::unordered_set<EntityID> &getSet(glm::i32vec2 vec);

private:
	void moveEntities(std::mt19937 &rng);
	void stepInfect(std::mt19937 &rng);
	void stepRemove(std::mt19937 &rng);

	void insertSIR(EntityID id, Status status);

	void infect(EntityID id);
	void recover(EntityID id);
	auto recover(const std::unordered_set<EntityID>::const_iterator &iter);
};



class Grid2DSocial : public Grid2D{
protected:
	void setEntitiesTargetVel(std::mt19937 &rng) override;
};
