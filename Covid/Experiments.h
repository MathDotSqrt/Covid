#pragma once
#include "Common.h"
#include "Grid2D.h"
#include "Stat.h"
#include "Util.h"


//void print_statistics(const std::vector<Stat::Statistic> &statistics);

namespace Control {
	void populate(Grid2D &grid, int n_S, int n_I, int n_R, std::mt19937 &rng);
	
}