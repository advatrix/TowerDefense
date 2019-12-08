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
		std::pair<double, double> cords;
	public:
		virtual ~Tower() {}
		Tower() : strategy(nullptr), feature(nullptr), lastShot(0), cords() {}
		Tower(Feature* _feature, Strategy* _strategy, unsigned int _lastShot,
			std::pair<double, double> cords);

		inline strategyTypeEnum getStrategyType() const { return strategy->getType(); }
		virtual inline buildingTypeEnum getType() const { return buildingTypeEnum::tower; }

		virtual void update();

		void setFeature(Feature* f) { feature = f; }
		void setStrategy(Strategy* s) { strategy = s; }

		unsigned int getLevel() const { return feature->getLevel(); }


	};
}

#endif

