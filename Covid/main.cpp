#include <stdio.h>
#include <random>
#include <iostream>

#include "common.h"
#include "Grid2D.h"

int main(void) { 
	Grid2D<100> grid;

	
	std::random_device rd{};
	std::mt19937 rng(rd());
	std::uniform_real_distribution<f32> U(0, 1);
	

	for (int i = 0; i < 1000; i++) {
		Entity e(glm::vec2(U(rng), U(rng)), Status::SUSCEPTIBLE);
		grid.insertEntity(e);
	}

	std::cout << "Pause...";
	std::cin.get();
	return 0;
}

