#pragma once
#include <random>
#include <array>
#include <vector>
#include <set>

#include "common.h"
#include "Entity.h"
template<int N>
class Grid2D {

public:
	i32 insertEntity(Entity e) {
		entities.push_back(e);
		auto index = entities.size() - 1;
		
		int i = floor(e.pos.x);
		int j = floor(e.pos.y);
		grid[i + j * N].insert(index);
		return index;
	}

	void removeEntity(i32 index) {
		if (index < 0 || index > entities.size() - 1) {
			return;
		}

		const auto &e = entities[index];
		int i = floor(e.pos.x);
		int j = floor(e.pos.y);
		std::set<i32> &set = grid[i + j * N];

		std::erase(set.find(index));
	}

private:
	std::vector<Entity> entities;
	std::array<std::set<i32>, N*N> grid;


};