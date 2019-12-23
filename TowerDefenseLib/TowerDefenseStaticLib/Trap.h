/**
\file
This file contains implementation of the Trap class
*/
#ifndef _TRAP_H_
#define _TRAP_H_

#include "Table.h"

#include "MagicEntity.h"
#include "Building.h"

namespace ct = customTemplates;

namespace TD {
	/**
	This class describe states of every trap in the game
	*/
	class Trap : public Building, public MagicEntity {
		ct::Table<Enemy*>* enemyTable; ///< A pointer to the table of the enemies currently alive
	public:
		Trap() : Building(), MagicEntity(), enemyTable(nullptr) {}
		Trap(std::pair<double, double> c, Effect* eff, ct::Table<Enemy*>* et) : 
			Building(c), MagicEntity(eff) {
			enemyTable = et;
		}

		/**
		This function is called every game tick and checks whether there are enemies directly on the trap and applies an effect on them if necessary.
		*/
		void update();
		buildingTypeEnum getType() const { return buildingTypeEnum::trap; }

		inline void applyEffect(Enemy* e) { e->addEffect(effect->copy()); }

	};
}


#endif