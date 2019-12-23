#include "pch.h"
#include "Lire.h"

namespace TD {
	void Lire::update() {
		spawn();
		internalTime++;
	}

	void Lire::spawn() {
		auto eqRange = schedule.equal_range(internalTime);
		
		for (auto it = eqRange.first; it != eqRange.second; ++it)
			spawn(it->second);
	}

	void Lire::spawn(Enemy* e) {
		e->revive();
		e->place(cords);
		enemyTable->insert(e);
	}
}