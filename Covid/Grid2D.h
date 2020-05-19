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
	void update(std::mt19937 &rng) override;
	void clear() override;
	
	f32 getMin() const override;
	f32 getMax() const override;
	
	f32 getQuadWidth() const;

	static constexpr float MAX = GRID_WIDTH;
	static constexpr float MIN = 0;
protected:
	std::unordered_set<EntityID> new_I;
	std::unordered_set<EntityID> new_R;

	//spacially partitioned datastructure
	std::array<std::unordered_set<EntityID>, NUM_GRIDS*NUM_GRIDS> grid;
	
	virtual void setEntitiesTargetVel(std::mt19937 &rng);
	glm::i32vec2 getQuad(const glm::vec2 &pos);
	std::unordered_set<EntityID> &getSet(int c, int r);
	std::unordered_set<EntityID> &getSet(glm::i32vec2 vec);

	virtual void moveEntities(std::mt19937 &rng);
	virtual void stepInfect(std::mt19937 &rng);
	void stepRemove(std::mt19937 &rng);

	void insertSIR(EntityID id, Status status);
	void infect(EntityID id);
	void recover(EntityID id);
	auto recover(const std::unordered_set<EntityID>::const_iterator &iter);
};


//class implements social distancing
class Grid2DSocial : public Grid2D{
protected:
	void setEntitiesTargetVel(std::mt19937 &rng) override;
};
