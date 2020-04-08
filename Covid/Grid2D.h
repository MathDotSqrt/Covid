#pragma once
#include <array>
#include <vector>
#include <unordered_set>
#include <stdio.h>

#include "common.h"
#include "Entity.h"
#include "Util.h"


template<int N>
class Grid2D {

public:
	int count = 0;

	i32 insertEntity(Entity e) {
		entities.push_back(e);
		auto id = entities.size() - 1;
		
		glm::i32vec2 quadrant = glm::floor(e.pos);
		getSet(quadrant).insert(id);


		insertSIR(id, e.status);
		return id;
	}

	void update(std::mt19937 &rng) {
		moveEntities(rng);
		stepInfect(rng);
		stepRemove(rng);
		Util::move_elements(I, new_I);
		Util::move_elements(R, new_R);
	}
	
	const std::vector<Entity> &getEntities() {
		return entities;
	}
	
	const std::unordered_set<i32> &getS() {
		return S;
	}

	const std::unordered_set<i32> &getI() {
		return I;
	}

	const std::unordered_set<i32> &getR() {
		return R;
	}

private:
	void moveEntities(std::mt19937 &rng) {
		for (int i = 0; i < entities.size(); i++) {
			auto &e = entities[i];
			const glm::i32vec2 prev_quadrant = glm::floor(e.pos);
			Util::move_unit(e, 0, N, rng);
			const glm::i32vec2 current_quadrant = glm::floor(e.pos);

			if (current_quadrant != prev_quadrant) {
				auto &old_set = getSet(prev_quadrant);
				auto &new_set = getSet(current_quadrant);

				old_set.erase(old_set.find(i));
				new_set.emplace(i);
				count++;
			}
		}
	}

	void stepInfect(std::mt19937 &rng) {
		auto interaction = [this](i32 id) {
			this->infect(id);
		};
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				for (const auto subjectID : getSet(c, r)) {
					const auto &entity = entities[subjectID];

					auto simulate_subject = [&](auto &quadrant) {
						Util::test_transmission(entity, this->entities, quadrant, interaction, rng);
					};

					Util::iterate_neighbors<N>(r, c, grid, simulate_subject);

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

	auto recover(const std::unordered_set<i32>::const_iterator &iter) {
		const auto id = *iter;
		auto &e = entities[id];
		assert(e.status == Status::INFECTED);
		e.status = Status::REMOVED;
		new_R.insert(id);
		return I.erase(iter);
	}

	std::vector<Entity> entities;
	std::unordered_set<i32> S;
	std::unordered_set<i32> I;
	std::unordered_set<i32> R;

	std::unordered_set<i32> new_I;
	std::unordered_set<i32> new_R;

	std::array<std::unordered_set<i32>, N*N> grid;

};