#include "pch.h"

#include <stdexcept>

#include "Building.h"



namespace TD {
	Building::Building(std::pair<double, double>* c) {
		if (!c) throw std::invalid_argument("cords nullptr");
		cords = c;
		
	}
}
