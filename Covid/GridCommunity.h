#pragma once
#include "Grid2D.h"

//test the deal with grid2D social
class GridCommunity : public Grid2D {

protected:
	void moveEntities(std::mt19937 &rng) override;
	void stepInfect(std::mt19937 &rng) override;
};

class GridCommunityFar : public GridCommunity {
protected:
	void moveEntities(std::mt19937 &rng) override;
};

class GridCommunityHub : public GridCommunityFar {
protected:
	void stepInfect(std::mt19937 &rng) override;
};


class GridCommunityHubRemove : public GridCommunityHub {
protected:
	void moveEntities(std::mt19937 &rng) override;
	void stepInfect(std::mt19937 &rng) override;
};
