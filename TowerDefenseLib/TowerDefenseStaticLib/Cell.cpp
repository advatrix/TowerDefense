#include "pch.h"
#include "Cell.h"

namespace TD {
	cellTypeEnum Cell::type = forest;

	Cell::Cell() {
		x = 0;
		y = 0;
	}

	Cell::Cell(int x_, int y_) {
		if (x_ < 0 || y_ < 0) throw std::invalid_argument("negative cords");
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
		building = bld;
		Castle* possibleCastlePtr = nullptr;
		try {
			possibleCastlePtr = dynamic_cast<Castle*>(bld);
		}
		catch (...) {
			return;
		}
		if (possibleCastlePtr) becomeDestination();
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
		dist = std::numeric_limits<int>::max();
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
		dist = std::numeric_limits<int>::max();
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



}
