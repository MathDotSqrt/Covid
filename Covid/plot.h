#pragma once
#include "olcPixelGameEngine.h"

#include "Experiments.h"
#include "GridCommunity.h"

class PlotControl : public olc::PixelGameEngine {
private:
	std::mt19937 rng;

	olc::Sprite *s = nullptr;
	olc::Decal *d = nullptr;

	/*
	
	Control
	Social Distancing
	Social Distancing (Bad)
	Community
	Community (Bad)
	Community Hub (Low)
	Community Hub (High)
	Community Hub (High)(Testing & Removal)
	
	
	*/


	//Grid2D grid;
	Grid2D grid;
	//GridCommunityHubRemove grid;

public:
	PlotControl(std::string name);
	PlotControl(std::string name, u32 seed);
	bool OnUserCreate() override;
	bool OnUserDestroy() override;
	bool OnUserUpdate(float delta) override;
};