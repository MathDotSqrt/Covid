#pragma once
#include <array>
#include <vector>
#include <unordered_set>
#include <stdio.h>

#include "Grid.h"
#include "Util.h"
#include <random>

template<int N>
class Grid2D : public Grid{

public:
	

	EntityID insert(Entity e) override {
		entities.push_back(e);
		auto id = entities.size() - 1;
		
		glm::i32vec2 quadrant = glm::floor(e.pos);
		getSet(quadrant).insert(id);


		insertSIR(id, e.status);
		return id;
	}

	void update(std::mt19937 &rng) override {
		moveEntities(rng);
		stepInfect(rng);
		stepRemove(rng);
		Util::move_elements(I, new_I);
		Util::move_elements(R, new_R);
	}
	
	void clear() override {
		entities.clear();
		S.clear();
		I.clear();
		R.clear();
		new_I.clear();
		new_R.clear();

		std::for_each(begin(grid), end(grid), [](auto &grid) {
			grid.clear();
		});
	}

	f32 getMin() const override {
		return MIN;
	}

	f32 getMax() const override {
		return MAX;
	}
	static constexpr float MAX = N;
	static constexpr float MIN = 0;
private:

	void moveEntities(std::mt19937 &rng) {
		
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				for (const auto subjectID : getSet(c, r)) {
					auto &entity = entities[subjectID];
					//entity.vel = glm::vec2(0);
					Util::entity_target_vel_smart(entity, rng);
					auto lambda = [subjectID, &entity, this](EntityID entityID) {
						if (subjectID == entityID) return;
						
						Util::charge_entity(entity, this->entities[entityID]);
						Util::charge_entity_wall(entity, MIN, MAX);
					};

					Util::for_each_neighbors<N>(r, c, grid, lambda);

				}
			}
		}

		for (size_t i = 0; i < entities.size(); i++) {
			auto &e = entities[i];
			const glm::i32vec2 prev_quadrant = glm::floor(e.pos);
			
			Util::move_entity(e);
			Util::clamp_entity(e, MIN, MAX);

			const glm::i32vec2 current_quadrant = glm::floor(e.pos);

			if (current_quadrant != prev_quadrant) {
				auto &old_set = getSet(prev_quadrant);
				auto &new_set = getSet(current_quadrant);

				old_set.erase(old_set.find(i));
				new_set.emplace(i);
			}
		}
	}

	void stepInfect(std::mt19937 &rng) {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				for (const auto subjectID : getSet(c, r)) {
					const auto &entity = entities[subjectID];
					
					if (entity.status != Status::INFECTED)
						continue;

					auto simulate_subject = [this, &entity, &rng](auto &id) {
						const Entity &subject = entities[id];
						if (Util::test_transmission(entity, entities[id], rng)) {
							this->infect(id);
						}
					};

					Util::for_each_neighbors<N>(r, c, grid, simulate_subject);

				}
			}
		}
	}

	void stepRemove(std::mt19937 &rng) {
		auto iter = I.begin();
		while (iter != I.end()) {
			if (Util::random_percent(GAMMA, rng)) {
				iter = recover(iter);
			}
			else{
				iter++;
			}
		}
	}

	std::unordered_set<i32> &getSet(int c, int r) {
		const int grid_index = c + r * N;
		return grid[grid_index];
	}

	std::unordered_set<i32> &getSet(glm::i32vec2 vec) {
		return getSet(vec.x, vec.y);
	}

	void insertSIR(i32 id, Status status) {
		switch (status) {
		case Status::SUSCEPTIBLE: S.insert(id); break;
		case Status::INFECTED: I.insert(id); break;
		case Status::REMOVED: R.insert(id); break;
		}
	}

	void infect(i32 id) {
		auto &e = entities[id];
		assert(e.status == Status::SUSCEPTIBLE);
		e.status = Status::INFECTED;
		S.erase(id);
		new_I.insert(id);
	}

	void recover(i32 id) {
		auto &e = entities[id];
		assert(e.status == Status::INFECTED);

		e.status = Status::REMOVED;
		I.erase(id);
		new_R.insert(id);
	}

	auto recover(const std::unordered_set<EntityID>::const_iterator &iter) {
		const auto id = *iter;
		auto &e = entities[id];
		assert(e.status == Status::INFECTED);
		e.status = Status::REMOVED;
		new_R.insert(id);
		return I.erase(iter);
	}

	std::unordered_set<i32> new_I;
	std::unordered_set<i32> new_R;

	std::array<std::unordered_set<i32>, N*N> grid;

};