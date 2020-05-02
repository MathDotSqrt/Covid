#include "Grid.h"


const std::vector<Entity> &Grid::getEntities() const {
	return entities;
}

const std::unordered_set<Grid::EntityID> &Grid::getS() const {
	return S;
}

const std::unordered_set<Grid::EntityID> &Grid::getI() const {
	return I;
}

const std::unordered_set<Grid::EntityID> &Grid::getR() const {
	return R;
}