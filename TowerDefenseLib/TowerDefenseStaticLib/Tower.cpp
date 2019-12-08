#include "pch.h"
#include "Tower.h"

namespace TD {

	Tower::Tower(Feature* _feature, Strategy* _strategy, unsigned int _lastShot, std::pair<double, double> _cords) {
		if (_feature) feature = _feature;
		else throw std::invalid_argument("feature nullptr");
		if (!_strategy) throw std::invalid_argument("strategy nullptr");
		strategy = _strategy;
		lastShot = _lastShot;
		cords = _cords;
	}

	void Tower::update() {
		if (lastShot > feature->getShotSpeed()) {
			Enemy* target = strategy->getTarget(cords, feature->getRadius());
			target->makeDamage(feature->getDamage());
			lastShot = 0;
		}
		else lastShot++;
	}
}