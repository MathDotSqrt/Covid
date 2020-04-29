#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Experiments.h"


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

		const olc::vf2d scale { .05f, .05f };

		grid.update(rng);
		for (const auto &e : grid.getEntities()) {
			const auto pos = olc::vf2d{ e.pos.x, e.pos.y } * SCREEN_SPACE;
			switch (e.status) {
			case Status::SUSCEPTIBLE:
				DrawDecal(pos, d, scale, olc::BLUE);
				break;
			case Status::INFECTED:
				DrawDecal(pos, d, scale, olc::RED);
				break;
			case Status::REMOVED:
				DrawDecal(pos, d, scale, olc::GREY);
				break;
			}
		}

		return grid.getI().size() > 0;
	}
};