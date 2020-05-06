#include "plot.h"
#include "plot.h"

void DrawEntity(olc::PixelGameEngine &engine, const Entity &e, olc::Decal *d) {
	constexpr float space = float(SCREEN_WIDTH) / Grid2D<NUM_GRIDS>::MAX;
	constexpr float scale = .01f;

	const auto offset = olc::vf2d{ d->sprite->width * scale / 2 , d->sprite->height * scale / 2 };
	const auto pos = olc::vf2d{ e.pos.x, e.pos.y } *space - offset;

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

i32 ControlBackground(olc::PixelGameEngine &engine, int N) {
	const auto layerID = engine.CreateLayer();
	engine.SetDrawTarget(layerID);
	engine.Clear(olc::Pixel(240,240,240));
	
	for (int r = 0; r < N; r++) {
		const float y = float(r * SCREEN_HEIGHT) / N;
		const olc::vf2d pos0 = { 0, y };
		const olc::vf2d pos1 = { float(SCREEN_WIDTH), y };
		engine.DrawLine(pos0, pos1, olc::Pixel(20, 20, 20));
	}

	for (int c = 0; c < N; c++) {
		const float x = float(c * SCREEN_WIDTH) / N;
		const olc::vf2d pos0 = { x, 0 };
		const olc::vf2d pos1 = { x, float(SCREEN_HEIGHT) };
		engine.DrawLine(pos0, pos1, olc::Pixel(20,20,20));
	}

	engine.EnableLayer(layerID, true);
	engine.SetDrawTarget(nullptr);
	return layerID;
}

PlotControl::PlotControl(std::string name) : rng(std::random_device()()) {
	this->sAppName = name;
}

PlotControl::PlotControl(std::string name, u32 seed) : rng(seed) {
	this->sAppName = name;
}

bool PlotControl::OnUserCreate() {
	s = new olc::Sprite("../data/res/circle.png");
	d = new olc::Decal(s);

	Control::populate(grid, 5000, 10, 0, rng);
	ControlBackground(*this, NUM_GRIDS);

	return true;
}

bool PlotControl::OnUserDestroy() {
	delete s;
	delete d;
	return true;
}

bool PlotControl::OnUserUpdate(float delta) {
	Clear(olc::BLANK);

	grid.update(rng);

	for (const auto &e : grid.getEntities()) {
		DrawEntity(*this, e, d);
	}


	return grid.getI().size() > 0;
}