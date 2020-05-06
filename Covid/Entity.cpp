#include "Entity.h"

Entity::Entity(glm::vec2 pos) : pos(pos), vel(0), status(Status::SUSCEPTIBLE) {}
Entity::Entity(glm::vec2 pos, Status status) : pos(pos), vel(0), status(status) {}
Entity::Entity(glm::vec2 pos, glm::vec2 vel, Status status) : pos(pos), vel(vel), status(status) {}
