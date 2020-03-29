#include "Entity.h"

Entity::Entity(glm::vec2 pos) : pos(pos), status(Status::SUSCEPTIBLE) {}
Entity::Entity(glm::vec2 pos, Status status) : pos(pos), status(status) {}