#pragma once
#include "Common.h"
#include "Grid2D.h"
#include "Stat.h"
#include "Util.h"


//void print_statistics(const std::vector<Stat::Statistic> &statistics);

namespace Control {
	template<int N>
	void populate(Grid2D<N> &grid, int n_S, int n_I, int n_R, std::mt19937 &rng) {
		std::uniform_real_distribution<f32> U(0, N);

		for (int i = 0; i < n_S; i++) {
			Entity e(glm::vec2(U(rng), U(rng)), Status::SUSCEPTIBLE);
			grid.insert(e);
		}

		for (int i = 0; i < n_I; i++) {
			Entity e(glm::vec2(U(rng), U(rng)), Status::INFECTED);
			grid.insert(e);
		}

		for (int i = 0; i < n_R; i++) {
			Entity e(glm::vec2(U(rng), U(rng)), Status::REMOVED);
			grid.insert(e);
		}
	}
	
}