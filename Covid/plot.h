#pragma once
#include "olcPixelGameEngine.h"

#include "Experiments.h"

class PlotControl : public olc::PixelGameEngine {
private:
	std::mt19937 rng;

	olc::Sprite *s = nullptr;
	olc::Decal *d = nullptr;
	Grid2DSocial<NUM_GRIDS> grid;

public:
	PlotControl(std::string name);
	PlotControl(std::string name, u32 seed);
	bool OnUserCreate() override;
	bool OnUserDestroy() override;
	bool OnUserUpdate(float delta) override;
};