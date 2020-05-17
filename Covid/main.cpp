/*
Control:
S: 16.6 +- 1.17
R: 5033.3 +- 1.17

Social:

*/

#include <stdio.h>
#include <random>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


#define OLC_PGE_APPLICATION
#include "plot.h"


#include "Stat.h"
#include "common.h"
#include "Grid2D.h"

typedef std::pair<std::vector<Stat::Statistic>, std::mutex> ThreadVector;

template<typename T>
Stat::Statistic run_experiment(std::mt19937 &rng) {
	T control{};
	Control::populate(control, SUSCEPTIBLE, INFECTED, 0, rng);

	int i = 0;
	while (control.getI().size() > 10) {
		control.update(rng);
		i++;
	}

	Stat::Statistic s;
	s.num_steps = i;
	s.num_susceptible = control.getS().size();
	s.num_removed = control.getR().size();

	return s;
}

template<typename T>
void worker_thread(ThreadVector *vector, i32 block_size, i64 seed) {
	std::mt19937 rng(seed);

	std::vector<Stat::Statistic> statistics;

	for (int i = 0; i < block_size; i++) {
		statistics.push_back(run_experiment<T>(rng));
	}

	auto &global_vector = vector->first;
	auto &mutex = vector->second;

	{
		std::lock_guard<std::mutex> lock(mutex);
		global_vector.insert(global_vector.end(), statistics.begin(), statistics.end());
	}

	std::cout << "Thread Exit.\n";
}

template<typename T>
void launch(int num_threads, int num_experiments, std::mt19937 &rng) {
	
	const auto BLOCK_SIZE = (i32)glm::ceil((f32)num_experiments / num_threads);

	ThreadVector worker_output;

	std::vector<std::thread> workers;

	for (int i = 0; i < num_threads - 1; i++) {
		std::cout << "Launching Thread[" << i << "] Block_Size = " << BLOCK_SIZE << "\n";
		workers.emplace_back(&worker_thread<T>, &worker_output, BLOCK_SIZE, rng());
	}
	std::cout << "Launching Thread[" << num_threads-1 << "] Block_Size =" << num_experiments - BLOCK_SIZE * (NUM_THREADS - 1)  <<"\n";
	workers.emplace_back(&worker_thread<T>, &worker_output, num_experiments - BLOCK_SIZE * (NUM_THREADS - 1), rng());

	for (int i = 0; i < num_threads; i++) {
		workers[i].join();
	}


	std::cout << "Total Stats: " << worker_output.first.size() << "\n";
	//do statistics
}


void visual(std::mt19937 &rng) {
	{
		PlotControl basicPlot("Basic", 1);
		if (basicPlot.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 4,4)) {
		
			basicPlot.Start();
		}
	}
}

template<typename T>
void fileout(std::mt19937 &rng) {
	std::ofstream out;
	out.open("./../data/final_output/CommunityHubLowTesting/output.csv");
	out << "infected,suceptible,removed\n";
	int i = 0;

	T control;

	while (control.getI().size()) {
		control.update(rng);
		out << control.getI().size()<< "," << control.getS().size() << "," << control.getR().size() << "\n";
		i++;
	}
	out.close();
}

int main(void) { 
	using namespace std::chrono;

	std::mt19937 rng(12371237);
	
	const auto start = high_resolution_clock::now();

	launch<Grid2DSocial>(NUM_THREADS, NUM_EXPERIMENTS, rng);
	//visual(rng);
	//fileout<Grid2D>(rng);

	const auto end = high_resolution_clock::now();
	
	std::cout << "Total execution time: " << duration_cast<seconds>(end - start).count() << "s\n";
	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

