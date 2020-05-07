#include "GridCommunity.h"


void GridCommunity::moveEntities(std::mt19937 &rng) {
	setEntitiesTargetVel(rng);

	for (size_t i = 0; i < entities.size(); i++) {
		auto &e = entities[i];
		const glm::i32vec2 prev_quadrant = getQuad(e.pos);
		const glm::vec2 min(prev_quadrant);
		Util::move_entity(e);
		if(e.bad_actor == false)
			Util::clamp_entity(e, min, min + glm::vec2(getQuadWidth()));
		Util::clamp_entity(e, getMin(), getMax());

		const glm::i32vec2 current_quadrant = getQuad(e.pos);

		if (current_quadrant != prev_quadrant) {
			auto &old_set = getSet(prev_quadrant);
			auto &new_set = getSet(current_quadrant);

			old_set.erase(old_set.find(i));
			new_set.emplace(i);
		}
	}

}

void GridCommunity::stepInfect(std::mt19937 &rng) {
	for (int r = 0; r < NUM_GRIDS; r++) {
		for (int c = 0; c < NUM_GRIDS; c++) {
			const auto &set = getSet(c, r);
			for (const auto subjectID : set) {
				const auto &entity = entities[subjectID];

				if (entity.status != Status::INFECTED) {
					continue;
				}

				for (const auto victim : set) {
					const auto &victim_entity = entities[victim];
					if (Util::test_transmission(entity, victim_entity, rng)) {
						infect(victim);
					}
				}
			}
		}
	}
}

void GridCommunityFar::moveEntities(std::mt19937 &rng) {
	setEntitiesTargetVel(rng);

	for (size_t i = 0; i < entities.size(); i++) {
		auto &e = entities[i];

		const glm::i32vec2 prev_quadrant = getQuad(e.pos);


		

		Util::move_entity(e);
		const glm::vec2 min(prev_quadrant);
		Util::clamp_entity(e, min, min + glm::vec2(getQuadWidth()));

		if (e.bad_actor) {
			Util::random_teleport(e, getMin(), getMax(), TELEPORT, rng);
		}

		Util::clamp_entity(e, getMin(), getMax());

		const glm::i32vec2 current_quadrant = getQuad(e.pos);

		if (current_quadrant != prev_quadrant) {
			auto &old_set = getSet(prev_quadrant);
			auto &new_set = getSet(current_quadrant);

			old_set.erase(old_set.find(i));
			new_set.emplace(i);
		}
	}
}