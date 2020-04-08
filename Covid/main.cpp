#include <stdio.h>
#include <random>
#include <iostream>

#include "Stat.h"
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

template<int N>
Stat::Statistic run_experiment(Grid2D<N> &grid, std::mt19937 &rng) {
	grid.clear();
	populate(grid, 5000, 10, 0, rng);

	int count = 0;
	while (grid.getI().size()) {
		grid.update(rng);
		create_plot(0.0f, N);
		plot_entities(grid.getEntities(), grid.getS(), "blue");
		plot_entities(grid.getEntities(), grid.getI(), "red");
		//plot_entities(grid.getEntities(), grid.getR(), "grey");
		plot_wait();
		count++;
	}

	return { (float)grid.getS().size(), (float)grid.getR().size(), (float)count };
}

void print_statistics(const std::vector<Stat::Statistic> &statistics) {
	const auto sample_mean = Stat::sample_mean(statistics);
	const auto sample_var = Stat::sample_variance(sample_mean, statistics);
	Stat::print_stat(sample_mean);
	Stat::print_stat(sample_var);
}

int main(void) { 
	constexpr int N = 20;
	Grid2D<N> grid;
	
	std::random_device rd{};
	std::mt19937 rng(rd());
		
	std::vector<Stat::Statistic> statistics;

	for (int i = 0; i < 5; i++) {
		statistics.push_back(run_experiment(grid, rng));
		Stat::print_stat(statistics.back());
	}

	print_statistics(statistics);

	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

