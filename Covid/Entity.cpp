#include "Entity.h"

Entity::Entity(glm::vec2 pos) : pos(pos), vel(0), status(Status::SUSCEPTIBLE), bad_actor(false){}
Entity::Entity(glm::vec2 pos, Status status) : pos(pos), vel(0), status(status), bad_actor(false) {}
Entity::Entity(glm::vec2 pos, glm::vec2 vel, Status status) : pos(pos), vel(vel), status(status), bad_actor(false) {}
Entity::Entity(glm::vec2 pos, Status status, bool bad_actor) : pos(pos), vel(0), status(status), bad_actor(bad_actor) {}
Entity::Entity(glm::vec2 pos, glm::vec2 vel, Status status, bool bad_actor) : pos(pos), vel(vel), status(status), bad_actor(bad_actor) {}
