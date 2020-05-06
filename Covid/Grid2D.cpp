#include "Grid2D.h"

Grid::EntityID Grid2D::insert(Entity e) {
	entities.push_back(e);
	auto id = entities.size() - 1;

	glm::i32vec2 quadrant = glm::floor(e.pos);
	getSet(quadrant).insert(id);


	insertSIR(id, e.status);
	return id;
}

void Grid2D::update(std::mt19937 &rng) {
	moveEntities(rng);
	stepInfect(rng);
	stepRemove(rng);
	Util::move_elements(I, new_I);
	Util::move_elements(R, new_R);
}

void Grid2D::clear() {
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

f32 Grid2D::getMin() const {
	return MIN;
}

f32 Grid2D::getMax() const {
	return MAX;
}

void Grid2D::moveEntities(std::mt19937 &rng) {
	setEntitiesTargetVel(rng);
	for (size_t i = 0; i < entities.size(); i++) {
		auto &e = entities[i];
		const glm::i32vec2 prev_quadrant = getQuad(e.pos);

		Util::move_entity(e);
		Util::clamp_entity(e, MIN, MAX);

		const glm::i32vec2 current_quadrant = getQuad(e.pos);

		if (current_quadrant != prev_quadrant) {
			auto &old_set = getSet(prev_quadrant);
			auto &new_set = getSet(current_quadrant);

			old_set.erase(old_set.find(i));
			new_set.emplace(i);
		}
	}
}

void Grid2D::stepInfect(std::mt19937 &rng) {
	for (int r = 0; r < NUM_GRIDS; r++) {
		for (int c = 0; c < NUM_GRIDS; c++) {
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

				Util::for_each_neighbors<NUM_GRIDS>(r, c, grid, simulate_subject);

			}
		}
	}
}
auto Grid2D::recover(const std::unordered_set<EntityID>::const_iterator &iter) {
	const auto id = *iter;
	auto &e = entities[id];
	assert(e.status == Status::INFECTED);
	e.status = Status::REMOVED;
	new_R.insert(id);
	return I.erase(iter);
}
void Grid2D::stepRemove(std::mt19937 &rng) {
	auto iter = I.begin();
	while (iter != I.end()) {
		if (Util::random_percent(GAMMA, rng)) {
			iter = recover(iter);
		}
		else {
			iter++;
		}
	}
}

glm::i32vec2 Grid2D::getQuad(const glm::vec2 &pos) {
	return glm::floor(pos);
}

std::unordered_set<Grid::EntityID> &Grid2D::getSet(int c, int r) {
	const int grid_index = c + r * NUM_GRIDS;
	return grid[grid_index];
}

std::unordered_set<Grid::EntityID> &Grid2D::getSet(glm::i32vec2 vec) {
	return getSet(vec.x, vec.y);
}

void Grid2D::insertSIR(EntityID id, Status status) {
	switch (status) {
	case Status::SUSCEPTIBLE: S.insert(id); break;
	case Status::INFECTED: I.insert(id); break;
	case Status::REMOVED: R.insert(id); break;
	}
}

void Grid2D::infect(EntityID id) {
	auto &e = entities[id];
	assert(e.status == Status::SUSCEPTIBLE);
	e.status = Status::INFECTED;
	S.erase(id);
	new_I.insert(id);
}

void Grid2D::recover(EntityID id) {
	auto &e = entities[id];
	assert(e.status == Status::INFECTED);

	e.status = Status::REMOVED;
	I.erase(id);
	new_R.insert(id);
}



//
void Grid2D::setEntitiesTargetVel(std::mt19937 &rng) {
	for (auto &entity : entities) {
		Util::entity_target_vel_smart(entity, MAX_MAGNITUDE, rng);
	}
}

void Grid2DSocial::setEntitiesTargetVel(std::mt19937 &rng) {
	for (int r = 0; r < NUM_GRIDS; r++) {
		for (int c = 0; c < NUM_GRIDS; c++) {
			for (const auto subjectID : Grid2D::getSet(c, r)) {
				auto &entity = Grid2D::entities[subjectID];

				Util::entity_target_vel_smart(entity, entity.bad_actor ? 10 * MAX_MAGNITUDE : MAX_MAGNITUDE, rng);
				auto lambda = [subjectID, &entity, this](Grid::EntityID entityID) {
					if (subjectID == entityID) return;

					Util::charge_entity(entity, this->entities[entityID]);
				};

				Util::for_each_neighbors<NUM_GRIDS>(r, c, Grid2D::grid, lambda);
			}
		}
	}
}
