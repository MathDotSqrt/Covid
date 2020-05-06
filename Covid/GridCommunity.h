#pragma once
#include "Grid2D.h"

class GridCommunity : public Grid2D {

protected:
	void moveEntities(std::mt19937 &rng) override;
	void stepInfect(std::mt19937 &rng) override;
};

