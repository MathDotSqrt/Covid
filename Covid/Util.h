#pragma once
#include "common.h"
#include "Entity.h"
#include <vector>
#include <random>
#include "glm.hpp"

constexpr f32 MAX_MAGNITUDE = 0.1f;
constexpr f32 PI = 3.14159265359f;
constexpr f32 EPSILON = 0.001f;

constexpr f32 RADIUS = .5f;
constexpr f32 RADIUS2 = RADIUS * RADIUS;

constexpr f32 BETA = 0.1f;


namespace Util {

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
	void interact(const Entity &infected, std::vector<Entity> &entities, std::unordered_set<i32> &quadrant, FUNC interaction, std::mt19937 &rng) {
		if (infected.status == Status::INFECTED) {
			std::uniform_real_distribution<f32> U(0, 1);

			std::for_each(begin(quadrant), end(quadrant), [&](const auto &id) {
				auto &e = entities[id];

				if (
					e.status == Status::SUSCEPTIBLE 
					&& glm::distance(infected.pos, e.pos) <= RADIUS 
					&& U(rng) <= BETA
				) {
					interaction(id);
				}
			});

		}
	}
}


