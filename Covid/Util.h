#pragma once
#include "common.h"
#include "Entity.h"
#include <vector>
#include <random>
#include <unordered_set>

#include "glm.hpp"



namespace Util {

	//true percent_true if the time
	bool random_percent(float percent_true, std::mt19937 &rng);
	
	//generates random velocity
	glm::vec2 random_vel(float max_mag, std::mt19937 &rng);
	
	//clamps entity position
	void clamp_entity(Entity &entity, f32 min, f32 max);
	
	//clamps entity position
	void clamp_entity(Entity &entity, glm::vec2 min, glm::vec2 max);
	
	//uses entity velocity to move position of entity
	void move_entity(Entity &entity);

	//randomly teleport entity percent of the time
	void random_teleport(Entity &entity, f32 min, f32 max, f32 percent, std::mt19937 &rng);
	
	//dumb movement code
	void entity_target_vel_random(Entity &entity, float max, std::mt19937 &rng);
	
	//smart movement code
	void entity_target_vel_smart(Entity &entity, float max, std::mt19937 &rng);
	
	//repelts entity from other using maxwells equations on static electro dynamics
	void charge_entity(Entity &entity, const Entity &other, float scale = 1);
	
	//broken
	void charge_entity_wall(Entity &entity, f32 min, f32 max);

	//test transmission of two entities
	bool test_transmission(const Entity &infected, const Entity &subject, std::mt19937 &rng);


	template<int N, typename FUNC>
	void for_each_neighbors(int r, int c, std::array<std::unordered_set<i32>, N*N> &grid, FUNC &function) {
		for (int j = -1; j <= 1; j++) {
			const int new_row = j + r;
			if (new_row < 0 || new_row >= N) {
				continue;
			}

			for (int i = -1; i <= 1; i++) {
				const int new_col = i + c;
				if (new_col < 0 || new_col >= N) {
					continue;
				}

				auto &set  = grid[new_col + new_row * N];
				//function(set);
				std::for_each(begin(set), end(set), function);
			}
		}
	}

	template<typename T>
	void insert_elements(T &dest, T &source) {
		for (const auto id : source) {
			dest.insert(id);
		}

		source.clear();
	}
	
}


