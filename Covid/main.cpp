#include <stdio.h>
#include <random>
#include <iostream>

#include "common.h"
#include "Grid2D.h"
#include "plot.h"




template<int N>
void populate(Grid2D<N> &grid, int n_S, int n_I, int n_R, std::mt19937 &rng) {
	std::uniform_real_distribution<f32> U(0, N);

	for (int i = 0; i < n_S; i++) {
		Entity e(glm::vec2(U(rng), U(rng)), Status::SUSCEPTIBLE);
		grid.insertEntity(e);
	}

	for (int i = 0; i < n_I; i++) {
		Entity e(glm::vec2(U(rng), U(rng)), Status::INFECTED);
		grid.insertEntity(e);
	}

	for (int i = 0; i < n_R; i++) {
		Entity e(glm::vec2(U(rng), U(rng)), Status::REMOVED);
		grid.insertEntity(e);
	}
}

int main(void) { 
	constexpr int N = 10;
	std::random_device rd{};
	std::mt19937 rng(rd());
	
	
	Grid2D<N> grid;
	populate(grid, 500, 1, 0, rng);
	
	for (int i = 0; i < 1000; i++) {
		grid.update(rng);
		create_plot(0.0f, N);
		plot_entities(grid.getEntities(), grid.getS(), "blue");
		plot_entities(grid.getEntities(), grid.getI(), "red");
		plot_wait();
	}

	std::cout << "COUNT: " << grid.count << std::endl;
	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

