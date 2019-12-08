#include "pch.h"
#include "Trap.h"

namespace TD {
	void Trap::update() {
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			std::pair<double, double> enemyCords = (*it)->getCords();
			if (floor(enemyCords.first) == cords->first &&
				floor(enemyCords.second == cords->second)) applyEffect((*it));
		}
	}
}
