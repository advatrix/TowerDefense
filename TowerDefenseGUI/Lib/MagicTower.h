/**
\file
This file contains implementation of MagicTower class
*/

#ifndef _MAGIC_TOWER_H_
#define _MAGIC_TOWER_H_

#include "Tower.h"
#include "MagicEntity.h"

namespace TD {
	/**
	This class describes state of Magic towers in the game
	*/
	class MagicTower : public Tower, public MagicEntity {
	public:
		MagicTower(): Tower(), MagicEntity(){}
		MagicTower(Feature* _feature, Strategy* _strategy, unsigned int _lastShot,
			std::pair<double, double> _cords, Effect* eff) :
			Tower(_feature, _strategy, _lastShot, _cords), MagicEntity(eff) {}

		/**
		This function is called every game tick.
		It attacks the enemies around the MagicTower instance and applies the Effects to them if necessary.
		*/
		void update();

		inline buildingTypeEnum getType() const { return buildingTypeEnum::magicTower; }

	};
}

#endif

