#include "Experiments.h"

void Control::populate(Grid2D &grid, int n_S, int n_I, int n_R, std::mt19937 &rng) {
	std::uniform_real_distribution<f32> U(grid.getMin() + EPSILON, grid.getMax() - EPSILON);

	for (int i = 0; i < n_S; i++) {
		bool bad_actor = Util::random_percent(BAD_ACTOR, rng);
		Entity e(glm::vec2(U(rng), U(rng)), Status::SUSCEPTIBLE, bad_actor);
		grid.insert(e);
	}

	for (int i = 0; i < n_I; i++) {
		bool bad_actor = Util::random_percent(BAD_ACTOR, rng);
		Entity e(glm::vec2(U(rng), U(rng)), Status::INFECTED, bad_actor);
		grid.insert(e);
	}

	for (int i = 0; i < n_R; i++) {
		bool bad_actor = Util::random_percent(BAD_ACTOR, rng);
		Entity e(glm::vec2(U(rng), U(rng)), Status::REMOVED, bad_actor);
		grid.insert(e);
	}
}