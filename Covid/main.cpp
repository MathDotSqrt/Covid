/*
Control:
S: 16.6 +- 1.17
R: 5033.3 +- 1.17

Social:

*/




#include <stdio.h>
#include <random>
#include <iostream>

#define OLC_PGE_APPLICATION
#include "plot.h"


#include "Stat.h"
#include "common.h"
#include "Grid2D.h"

Stat::Statistic run_experiment(std::mt19937 &rng) {
	Grid2DSocial control{};
	Control::populate(control, SUSCEPTIBLE, INFECTED, 0, rng);

	int i = 0;
	while (control.getI().size()) {
		control.update(rng);
		i++;
	}

	Stat::Statistic s;
	s.num_steps = i;
	s.num_susceptible = control.getS().size();
	s.num_removed = control.getR().size();

	return s;
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
	
	std::mt19937 rng(12371237);
	

	//std::ofstream out;
	//out.open("./../data/final_output/CommunityHubLowTesting/output.csv");
	//out << "infected,suceptible,removed\n";
	//int i = 0;
	//while (control.getI().size()) {
	//	control.update(rng);
	//	out << control.getI().size()<< "," << control.getS().size() << "," << control.getR().size() << "\n";
	//	i++;
	//}
	//out.close();

	{
		PlotControl basicPlot("Basic", 1);
		if (basicPlot.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 4,4)) {
			
			basicPlot.Start();
		}
	}

	//std::vector<Stat::Statistic> statistics;
	//for (int i = 0; i < NUM_EXPERIMENTS; i++) {
	//	statistics.push_back(run_experiment(rng));
	//	Stat::print_stat(statistics.back());
	//}
	//print_statistics(statistics);
	//std::cout << "Pause...";
	//std::cin.get();
	return 0;
}

