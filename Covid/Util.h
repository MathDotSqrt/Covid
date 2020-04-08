#pragma once
#include "common.h"
#include "Entity.h"
#include <vector>
#include <random>
#include "glm.hpp"




namespace Util {

	bool random_percent(float percent_true, std::mt19937 &rng) {
		const std::uniform_real_distribution<f32> U(0, 1);
		return U(rng) <= percent_true;
	}

	template<typename RNG>
	void move_unit(Entity &entity, f32 min, f32 max, RNG &rng) {
		const std::uniform_real_distribution<f32> U_MAG(0, MAX_MAGNITUDE);
		const std::uniform_real_distribution<f32> U_DIR(0, 2 * PI);

		const f32 rand_mag = U_MAG(rng);
		const f32 rand_dir = U_DIR(rng);

		const f32 X = rand_mag * glm::cos(rand_dir);
		const f32 Y = rand_mag * glm::sin(rand_dir);

		entity.pos += glm::vec2(X, Y);
		entity.pos = glm::clamp(entity.pos, glm::vec2(min), glm::vec2(max - EPSILON));
	}

	template<typename FUNC>
	void test_transmission(const Entity &infected, std::vector<Entity> &entities, std::unordered_set<i32> &quadrant, FUNC transmitted, std::mt19937 &rng) {
		if (infected.status == Status::INFECTED) {
			std::uniform_real_distribution<f32> U(0, 1);

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


