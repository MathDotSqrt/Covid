#pragma once
#include "common.h"
#include "Entity.h"
#include <vector>
#include <random>
#include <unordered_set>

#include "glm.hpp"



namespace Util {

	bool random_percent(float percent_true, std::mt19937 &rng);

	void move_entity(Entity &entity, f32 min, f32 max, std::mt19937 &rng);

	template<typename FUNC>
	void test_transmission(const Entity &infected, std::vector<Entity> &entities, std::unordered_set<i32> &quadrant, FUNC transmitted, std::mt19937 &rng) {
		if (infected.status == Status::INFECTED) {
			std::for_each(begin(quadrant), end(quadrant), [&](const auto &id) {
				auto &e = entities[id];

				if (
					e.status == Status::SUSCEPTIBLE 
					&& glm::distance(infected.pos, e.pos) <= RADIUS 
					&& Util::random_percent(BETA, rng)
				) {
					transmitted(id);
				}
			});

		}
	}

	template<int N, typename FUNC>
	void iterate_neighbors(int r, int c, std::array<std::unordered_set<i32>, N*N> &grid, FUNC &function) {
		for (int j = -1; j <= 1; j++) {
			const int new_row = j + r;
			if (new_row < 0 || new_row >= N) {
				continue;
			}

			for (int i = -1; i <= 1; i++) {
				const int new_col = i + c;
				if (new_col < 0 || new_col >= N) {
					continue;
				}

				auto &set  = grid[new_col + new_row * N];
				function(set);
			}
		}
	}

	template<typename T>
	void move_elements(T &dest, T &source) {
		for (const auto id : source) {
			dest.insert(id);
		}

		source.clear();
	}
	
}


