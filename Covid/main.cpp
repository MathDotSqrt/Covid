#include <stdio.h>
#include <random>
#include <iostream>

#define OLC_PGE_APPLICATION
#include "plot.h"


#include "Stat.h"
#include "common.h"
#include "Grid2D.h"



void print_statistics(const std::vector<Stat::Statistic> &statistics) {
	const auto sample_mean = Stat::sample_mean(statistics);
	const auto sample_var = Stat::sample_variance(sample_mean, statistics);
	Stat::print_stat(sample_mean);
	Stat::print_stat(sample_var);

	Stat::print_stat(sample_mean);
	Stat::print_stat(t_half_interval(t_05_100, Stat::sqrt(sample_var), NUM_EXPERIMENTS));
}

int main(void) { 
	
	//std::random_device rd{};
	//std::mt19937 rng(rd());
	//Grid2D control{};
	//Control::populate(control, 5000, 50, 0, rng);

	//std::ofstream out;
	//out.open("./../data/final_output/output.csv");
	//
	//int i = 0;
	//while (control.getI().size()) {
	//	control.update(rng);
	//	out << i << "," << control.getS().size() << "," << control.getI().size() << "," << control.getR().size() << "\n";
	//	

	//	i++;
	//}
	//out.close();

	{
		PlotControl basicPlot("Basic", 1);
		if (basicPlot.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1))
			basicPlot.Start();
	}

	//std::vector<Stat::Statistic> statistics;
	//for (int i = 0; i < NUM_EXPERIMENTS; i++) {
	//	statistics.push_back(run_experiment(grid, rng));
	//	Stat::print_stat(statistics.back());
	//}
	//print_statistics(statistics);
	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

