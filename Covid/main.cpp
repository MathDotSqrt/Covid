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
	//T is the experiment type
	T control{};

	//populate the experiment
	Control::populate(control, SUSCEPTIBLE, INFECTED, 0, rng);

	//update experiment until infected threshold is met
	int i = 0;
	while (control.getI().size() > 10) {
		control.update(rng);
		i++;
	}


	//statistics collected
	Stat::Statistic s;
	s.num_steps = i;
	s.num_susceptible = control.getS().size();
	s.num_removed = control.getR().size();

	return s;
}

template<typename T>
void worker_thread(ThreadVector *vector, i32 block_size, i64 seed) {
	//each thread needs its own rng machine
	std::mt19937 rng(seed);

	//stores results of all experiments
	std::vector<Stat::Statistic> statistics;

	//run experiments
	for (int i = 0; i < block_size; i++) {
		statistics.push_back(run_experiment<T>(rng));
	}

	auto &global_vector = vector->first;
	auto &mutex = vector->second;

	{
		//lock mutex to insert data into global vector
		std::lock_guard<std::mutex> lock(mutex);
		global_vector.insert(global_vector.end(), statistics.begin(), statistics.end());
	}

	std::cout << "Thread Exit.\n";
}

template<typename T>
void launch(int num_threads, int num_experiments, std::mt19937 &rng) {
	
	const auto FLOOR = (i32)glm::floor((f32)num_experiments / num_threads);
	const auto MOD = num_experiments % num_threads;

	//global vector for all threads to insert experiment
	//results in
	ThreadVector worker_output;

	//all worker threads
	std::vector<std::thread> workers;

	for (int i = 0; i < num_threads; i++) {

		//number of experiments to run for given thread
		const int BLOCK_SIZE = FLOOR + (i < MOD ? 1 : 0);

		std::cout << "Launching Thread[" << i << "] Block_Size = " << BLOCK_SIZE << "\n";
		workers.emplace_back(&worker_thread<T>, &worker_output, BLOCK_SIZE, rng());
	}

	//wait for all threads to finish execution
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
	
	//random_device generates the seed
	std::random_device rd;
	//mersen prime twiseter, state of the art uniform random number machine
	std::mt19937 rng(rd());

	const auto start = high_resolution_clock::now();

	//Launch one of them to run experiment
	launch<Grid2DSocial>(NUM_THREADS, NUM_EXPERIMENTS, rng);
	//visual(rng);
	//fileout<Grid2D>(rng);

	const auto end = high_resolution_clock::now();

	std::cout << "Total execution time: " << duration_cast<seconds>(end - start).count() << "s\n";
	
	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

