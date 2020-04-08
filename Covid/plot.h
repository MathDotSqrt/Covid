#pragma once

#include "Entity.h"
#include "matplotlib.h"
#include "Grid2D.h"

#ifndef _DEBUG
//#define MATPLOTLIB
#endif

namespace plt = matplotlibcpp;


void create_plot(float min, float max) {
#ifdef MATPLOTLIB
	plt::figure(1);
	plt::grid(true);
	plt::xlim(min, max);
	plt::ylim(min, max);

#endif
}

void plot_entities(const std::vector<Entity> &entities, const std::unordered_set<i32> &ids, const char *color) {
#ifdef MATPLOTLIB
	static std::vector<float> x;
	static std::vector<float> y;

	x.clear();
	y.clear();

	std::for_each(begin(ids), end(ids), [&](auto &id) {
		const auto &e = entities[id];

		x.push_back(e.pos.x);
		y.push_back(e.pos.y);
	});

	//std::string abc = "";

	plt::plot(x, y, { {"marker", "."}, {"linestyle", "none"}, {"color", color} });


#endif
}

void plot_wait() {
#ifdef MATPLOTLIB
	plt::pause(.001);
	plt::clf();
#endif
}