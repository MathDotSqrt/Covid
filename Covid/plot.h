#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Experiments.h"


void DrawEntity(olc::PixelGameEngine &engine, const Entity &e, olc::Decal *d, float scale, float space) {

	const auto offset = olc::vf2d{ d->sprite->width * scale / 2 , d->sprite->height * scale / 2 };
	const auto pos = olc::vf2d{ e.pos.x, e.pos.y } * space + offset;
	
	switch (e.status) {
	case Status::SUSCEPTIBLE:
		engine.DrawDecal(pos, d, { scale, scale }, olc::BLUE);
		break;
	case Status::INFECTED:
		engine.DrawDecal(pos, d, { scale, scale }, olc::RED);
		break;
	case Status::REMOVED:
		engine.DrawDecal(pos, d, { scale, scale }, olc::GREY);
		break;
	}
}

class PlotControl : public olc::PixelGameEngine {
private:
	std::mt19937 rng;

	olc::Sprite *s = nullptr;
	olc::Decal *d = nullptr;
	Grid2D<NUM_GRIDS> grid;

public:
	PlotControl(std::string name) : rng(std::random_device()()){
		this->sAppName = name;
	}

	PlotControl(std::string name, u32 seed) : rng(seed) {
		this->sAppName = name;
	}

	bool OnUserCreate() override {
		s = new olc::Sprite("../data/res/circle.png");
		d = new olc::Decal(s);

		Control::populate(grid, 5000, 10, 0, rng);

		return true;
	}

	bool OnUserDestroy() override {
		delete s;
		delete d;

		return true;
	}

	bool OnUserUpdate(float delta) override {
		Clear(olc::VERY_DARK_BLUE);
		constexpr float SCREEN_SPACE = float(SCREEN_WIDTH) / Grid2D<NUM_GRIDS>::MAX;
		constexpr float SCALE = .005f;

		grid.update(rng);
		for (const auto &e : grid.getEntities()) {
			DrawEntity(*this, e, d, SCALE, SCREEN_SPACE);
		}

		return grid.getI().size() > 0;
	}
};