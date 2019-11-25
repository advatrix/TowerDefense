#include "pch.h"
#include "Building.h"

namespace TD {
	Castle::Castle(Cell* cell, double curHp, double maxHp, int money, std::string title) {
		cell_ = cell;
		curHp_ = curHp;
		maxHp_ = maxHp;
		money_ = money;
		title_ = title;
	}

	Building::Building() {
		cell_ = nullptr;
	}

	Building::Building(Cell* cell) {
		cell_ = cell;
	}



}
