#pragma once
#include "common.h"
#include "Entity.h"
#include <vector>
#include <random>

constexpr f32 PI = 3.14159265359f;

template<typename RNG>
void move_unit(Entity &entity, f32 max_magnitude, RNG &rng) {
	const std::uniform_real_distribution<f32> U_MAG(0, max_magnitude);
	const std::uniform_real_distribution<f32> U_DIR(0, 2 * PI);

	const f32 rand_mag = U_MAG(rng);
	const f32 rand_dir = U_DIR(rng);

	const X = rand_mag * glm::cos(rand_dir);
	const Y = rand_mag * glm::sin(rand_dir);

	entity.pos += glm::vec2(X,Y);
}


