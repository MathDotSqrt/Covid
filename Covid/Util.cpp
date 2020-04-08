#include "Util.h"

bool Util::random_percent(float percent_true, std::mt19937 &rng) {
	const std::uniform_real_distribution<f32> U(0, 1);
	return U(rng) <= percent_true;
}