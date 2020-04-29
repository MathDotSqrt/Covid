#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

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

	//std::cout << "num_susceptible,num_infected,num_recovered\n";

	int count = 0;
	while (grid.getI().size()) {
		//std::cout << grid.getS().size() << ',' << grid.getI().size() << ',' << grid.getR().size() << '\n';
		grid.update(rng);
		//create_plot(0.0f, N);
		//plot_entities(grid.getEntities(), grid.getS(), "blue");
		//plot_entities(grid.getEntities(), grid.getI(), "red");
		//plot_entities(grid.getEntities(), grid.getR(), "grey");
		//plot_wait();
		count++;
	}

	return { (float)grid.getS().size(), (float)grid.getR().size(), (float)count };
}

void print_statistics(const std::vector<Stat::Statistic> &statistics) {
	const auto sample_mean = Stat::sample_mean(statistics);
	const auto sample_var = Stat::sample_variance(sample_mean, statistics);
	Stat::print_stat(sample_mean);
	Stat::print_stat(sample_var);

	Stat::print_stat(sample_mean);
	Stat::print_stat(t_half_interval(t_05_100, Stat::sqrt(sample_var), NUM_EXPERIMENTS));
}

int main(void) { 
	Grid2D<NUM_GRIDS> grid;
	
	std::random_device rd{};
	std::mt19937 rng(rd());
		
	std::vector<Stat::Statistic> statistics;
	for (int i = 0; i < NUM_EXPERIMENTS; i++) {
		statistics.push_back(run_experiment(grid, rng));
		Stat::print_stat(statistics.back());
	}
	print_statistics(statistics);

	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

