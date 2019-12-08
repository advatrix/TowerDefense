#include "pch.h"
#include "Cell.h"
#include "Trap.h"

namespace TD {

	Cell::Cell() {
		x = 0;
		y = 0;
	}

	Cell::Cell(int x_, int y_) {
		x = x_;
		y = y_;
	}

	std::pair<double, double> Cell::cords() const {
		return std::pair<double, double>(x, y);
	}


	void Road::makeWestEastNeighbours(Road* west, Road* east) {
		if (west->east || east->west) throw std::runtime_error("Redefining neighbours");
		west->east = east;
		east->west = west;
	}

	void Road::makeNorthSouthNeighbours(Road* north, Road* south) {
		if (south->north || north->south) throw std::exception("Redefining neighbours!");
		north->south = south;
		south->north = north;
	}

	void Road::clearPath() {
		next = nullptr;
		dist = std::numeric_limits<int>::max();
	}

	void Road::build(Building* bld) {
		if (building) throw std::runtime_error("Rebuilding");
		if (bld->getType() == buildingTypeEnum::tower ||
			bld->getType() == buildingTypeEnum::magicTower)
			throw std::invalid_argument("illegal building");
		building = bld;
		if (bld->getType() == buildingTypeEnum::castle) becomeDestination();
		
	}

	void Road::becomeDestination() {
		dist = 0;
		next = nullptr;
	}

	void Road::growPathTo(Road* neighbour) {
		if (!hasPath()) throw std::runtime_error("No path");
		if (!neighbour || neighbour->hasPath()) return;
		neighbour->dist = dist + 1;
		neighbour->next = this;
	}

	Road* Road::growPathToNeighbour(Road* neighbour) {
		if (!hasPath()) throw std::runtime_error("No path");
		if (!neighbour || neighbour->hasPath()) return nullptr;
		neighbour->dist = dist + 1;
		neighbour->next = this;
		return neighbour;
	}


	void Road::destroy() {
		Trap* possibleTrap;
		try {
			possibleTrap = dynamic_cast<Trap*>(building);
		}
		catch (...) {
			throw std::exception("impossible to destroy");
		}
		if (possibleTrap) delete building;
		else throw std::exception("impossible to destroy");
	}

	Road::Road(int i, int j) {
		building = nullptr;
		west = nullptr;
		east = nullptr;
		north = nullptr;
		south = nullptr;
		next = nullptr;
		dist = std::numeric_limits<unsigned>::max();
		x = i;
		y = j;
	}

	Road::Road() {
		building = nullptr;
		west = nullptr;
		east = nullptr;
		north = nullptr;
		south = nullptr;
		next = nullptr;
		dist = std::numeric_limits<unsigned>::max();
		x = 0;
		y = 0;
	}

	Road::~Road() {
		try {
			destroy();
		}
		catch (...) {
			;
		}
	}

	void Field::build(Tower* tw) {
		if (tw) tower = tw;
		else throw std::invalid_argument("tower nullptr");
	}

	Field::Field() {
		x = 0;
		y = 0;
		tower = nullptr;
	}

	Field::Field(int i, int j) {
		x = i;
		y = j;
		tower = nullptr;
	}

	Field::~Field() {
		delete tower;
	}

	void Field::destroy() {
		if (tower) delete tower;
	}


}
