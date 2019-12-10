#include "pch.h"
#include "MagicTower.h"

namespace TD {
	void MagicTower::update() {
		if (lastShot > feature->getShotSpeed()) {
			Enemy* target = strategy->getTarget(cords, feature->getRadius());
			target->makeDamage(feature->getDamage());
			applyEffect(target);
			lastShot = 0;
		}
		else lastShot++;
	}
}
