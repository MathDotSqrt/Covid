#pragma once
#include "common.h"
#include "glm.hpp"

enum class Status : u8{
	SUSCEPTIBLE,
	INFECTED,
	REMOVED
};

struct Entity {
	glm::vec2 pos;
	glm::vec2 vel;
	Status status;
	bool bad_actor;

	Entity(glm::vec2 pos);
	Entity(glm::vec2 pos, Status status);
	Entity(glm::vec2 pos, glm::vec2 vel, Status status);
	Entity(glm::vec2 pos, Status status, bool bad_actor);
	Entity(glm::vec2 pos, glm::vec2 vel, Status status, bool bad_actor);
};