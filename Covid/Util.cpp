#include "Util.h"

bool Util::random_percent(float percent_true, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U(0, 1);
	return U(rng) <= percent_true;
}


glm::vec2 Util::random_vel(float max_mag, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U_MAG(0, MAX_MAGNITUDE);
	const std::uniform_real_distribution<f32> U_DIR(0, 2 * PI);

	const f32 rand_mag = U_MAG(rng);
	const f32 rand_dir = U_DIR(rng);

	const f32 X = rand_mag * glm::cos(rand_dir);
	const f32 Y = rand_mag * glm::sin(rand_dir);

	return glm::vec2(X, Y);
}

void Util::move_entity(Entity &entity, f32 min, f32 max, std::mt19937 &rng) {
	entity.vel = random_vel(MAX_MAGNITUDE, rng);

	entity.pos += entity.vel;
	entity.pos = glm::clamp(entity.pos, glm::vec2(min + EPSILON), glm::vec2(max - EPSILON));
}

void Util::move_entity_smart(Entity &entity, f32 min, f32 max, std::mt19937 &rng) {
	if (Util::random_percent(CHANGE_DIR, rng)) {
		entity.vel = random_vel(MAX_MAGNITUDE, rng);
	}
	entity.pos += entity.vel;
	entity.pos = glm::clamp(entity.pos, glm::vec2(min + EPSILON), glm::vec2(max - EPSILON));
}

bool Util::test_transmission(const Entity &infected, const Entity &subject, std::mt19937 &rng) {
	return subject.status == Status::SUSCEPTIBLE
		&& glm::distance(infected.pos, subject.pos) <= RADIUS
		&& Util::random_percent(BETA, rng);
}

