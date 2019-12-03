#ifndef _MAGIC_TOWER_H_
#define _MAGIC_TOWER_H_

#include "Tower.h"
#include "MagicEntity.h"

namespace TD {
	class MagicTower : public Tower, public MagicEntity {
	public:
		MagicTower(): Tower(), MagicEntity(){}
		MagicTower(Feature* _feature, Strategy* _strategy, unsigned int _lastShot,
			std::pair<double, double>* _cords, Effect* eff) :
			Tower(_feature, _strategy, _lastShot, _cords), MagicEntity(eff) {}

		void update();

	};
}

#endif

