#include "Util.h"
#include "gtx/norm.hpp"

bool Util::random_percent(float percent_true, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U(0, 1);
	return U(rng) <= percent_true;
}

glm::vec2 Util::random_vel(float max_mag, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U_MAG(0, max_mag);
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

void Util::entity_target_vel_random(Entity &entity, float max, std::mt19937 &rng) {
	entity.vel = Util::random_vel(max, rng);
}

void Util::entity_target_vel_smart(Entity &entity, float max, std::mt19937 &rng) {
	if (Util::random_percent(CHANGE_DIR, rng)) {
		entity.vel = random_vel(max, rng);
	}
}

template<typename T>
T charge_force(const T &a, const T &other) {
	const auto delta = a - other;
	const float r_2 = glm::length2(delta);

	if (r_2 > MAX_CHARGE_DIST * MAX_CHARGE_DIST) {
		return T(0);
	}

	const float inv_r_2 = 1 / r_2;

	const auto coef = glm::min(CHARGE_CONSTANT / r_2, MAX_CHARGE);

	T force = coef * glm::normalize(delta);
	return force;
}

void Util::charge_entity(Entity &entity, const Entity &other, float scale) {
	//if both entities are not bad actors repel
	if (!entity.bad_actor && !other.bad_actor) {
		entity.vel += scale * charge_force<glm::vec2>(entity.pos, other.pos);
	}
}

void Util::charge_entity_wall(Entity &entity, f32 min, f32 max) {
	//entity.vel.x += charge_force<glm::vec1>((glm::vec1)entity.pos.x, (glm::vec1)min).x;
	//entity.vel.x += charge_force<glm::vec1>((glm::vec1)entity.pos.x, (glm::vec1)max).x;
	//entity.vel.y += charge_force<glm::vec1>((glm::vec1)entity.pos.y, (glm::vec1) min).x;
	//entity.vel.y += charge_force<glm::vec1>((glm::vec1)entity.pos.y, (glm::vec1)max).x;
}

bool Util::test_transmission(const Entity &infected, const Entity &subject, std::mt19937 &rng) {
	return subject.status == Status::SUSCEPTIBLE
		&& glm::distance(infected.pos, subject.pos) <= RADIUS
		&& Util::random_percent(BETA, rng);
}

