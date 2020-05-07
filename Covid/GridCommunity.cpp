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

void GridCommunityHub::stepInfect(std::mt19937 &rng) {
	GridCommunity::stepInfect(rng);

	
	const std::uniform_int_distribution<EntityID> U(0, entities.size() - 1);
	std::vector<EntityID> shopping;
	shopping.reserve(MAX_SHOP);

	//printf("hello\n");

	for (int i = 0; i < MAX_SHOP; i++) {
		EntityID rand_entity_id = U(rng);
		shopping.push_back(rand_entity_id);
	}
	
	for (int i = 0; i < MAX_SHOP; i++) {
		const auto subject_index = shopping[i];
		const auto &subject = entities[subject_index];
		for (int j = i + 1; j < MAX_SHOP; j++) {
			const auto infected_index = shopping[j];
			const auto &infected = entities[infected_index];
			if (infected.status == Status::INFECTED) {
				auto subject_shop = subject;
				auto infected_shop = infected;
				//make em relative to eachother very close
				subject_shop.pos = glm::mod(subject_shop.pos, glm::vec2(getQuadWidth()));
				infected_shop.pos = glm::mod(infected_shop.pos, glm::vec2(getQuadWidth()));
				if (Util::test_transmission(infected_shop, subject_shop, rng)) {
					infect(subject_index);
					break;
				}
			
			}
		}
	}

}