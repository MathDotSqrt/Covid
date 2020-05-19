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

	//uncomment one of these to run that form of simulation
	//Grid2D grid;				//control
	Grid2DSocial grid;		//social distancinv
	//GridCommunity grid;		//community
	//GridCommunityFar grid;	//comunaity with bad actors teleporting
	//GridCommunityHub grid;	//community with hub zones
	//GridCommunityHubRemove grid;	//grid community with testing
public:
	PlotControl(std::string name);
	PlotControl(std::string name, u32 seed);
	bool OnUserCreate() override;
	bool OnUserDestroy() override;
	bool OnUserUpdate(float delta) override;
};