#ifndef _TOWER_H_
#define _TOWER_H_

#include "Building.h"
#include "Feature.h"
#include "Strategy.h"

namespace TD {
	class Tower : public Building {
	protected:
		Strategy* strategy;
		Feature* feature;
		unsigned int lastShot;
		static buildingTypeEnum type;
		std::pair<double, double>* cords;
	public:
		virtual ~Tower() {}
		Tower() : strategy(nullptr), feature(nullptr), lastShot(0) {}
		Tower(Feature* _feature, Strategy* _strategy, unsigned int _lastShot,
			std::pair<double, double>* cords);

		inline strategyTypeEnum getStrategyType() const { return strategy->getType(); }

		virtual void update();
	};
}

#endif

