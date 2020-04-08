#include "Util.h"

bool Util::random_percent(float percent_true, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U(0, 1);
	return U(rng) <= percent_true;
}

void Util::move_entity(Entity &entity, f32 min, f32 max, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U_MAG(0, MAX_MAGNITUDE);
	const std::uniform_real_distribution<f32> U_DIR(0, 2 * PI);

	const f32 rand_mag = U_MAG(rng);
	const f32 rand_dir = U_DIR(rng);

	const f32 X = rand_mag * glm::cos(rand_dir);
	const f32 Y = rand_mag * glm::sin(rand_dir);

	entity.pos += glm::vec2(X, Y);
	entity.pos = glm::clamp(entity.pos, glm::vec2(min), glm::vec2(max - EPSILON));
}