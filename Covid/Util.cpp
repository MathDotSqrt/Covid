#include "Util.h"
#include "gtx/norm.hpp"

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

void Util::clamp_entity(Entity &entity, f32 min, f32 max) {
	entity.pos = glm::clamp(entity.pos, glm::vec2(min + EPSILON), glm::vec2(max - EPSILON));
}


void Util::move_entity(Entity &entity) {
	entity.pos += entity.vel;
}

void Util::move_entity_random(Entity &entity, std::mt19937 &rng) {
	entity.vel = Util::random_vel(MAX_MAGNITUDE, rng);
	//entity.pos += entity.vel;
}

void Util::move_entity_smart(Entity &entity, std::mt19937 &rng) {
	if (Util::random_percent(CHANGE_DIR, rng)) {
		entity.vel = random_vel(MAX_MAGNITUDE, rng);
	}
	//entity.pos += entity.vel;
}

void Util::charge_entity(Entity &entity, const Entity &other) {
	const auto delta = entity.pos - other.pos;
	const float r_2 = glm::length2(delta);
	if (r_2 <= EPSILON) {
		return;
	}
	
	const float inv_r_2 = 1 / r_2;

	entity.vel += CHARGE_CONSTANT * glm::normalize(delta) * inv_r_2;
}

bool Util::test_transmission(const Entity &infected, const Entity &subject, std::mt19937 &rng) {
	return subject.status == Status::SUSCEPTIBLE
		&& glm::distance(infected.pos, subject.pos) <= RADIUS
		&& Util::random_percent(BETA, rng);
}

