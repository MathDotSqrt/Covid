#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



class Plot : public olc::PixelGameEngine {
public:
	Plot(std::string name) {
		this->sAppName = name;
	}

	bool OnUserCreate() override {
		//init
		return true;
	}

	bool OnUserUpdate(float delta) override {
		// called once per frame, draws random coloured pixels
		Clear(olc::BLACK);
		for (uint8_t x = 0; x < 1; x++)
			for (uint8_t y = 0; y < 1; y++)
				DrawCircle(rand() % 256, rand() % 256, 5, olc::Pixel(255-x, 255-y, 255-x));
		return true;
	}
};