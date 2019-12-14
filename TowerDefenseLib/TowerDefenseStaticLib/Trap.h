#ifndef _TRAP_H_
#define _TRAP_H_

#include "Table.h"

#include "MagicEntity.h"
#include "Building.h"

namespace ct = customTemplates;

namespace TD {
	class Trap : public Building, public MagicEntity {
		ct::Table<Enemy*>* enemyTable;
	public:
		Trap() : Building(), MagicEntity(), enemyTable(nullptr) {}
		Trap(std::pair<double, double> c, Effect* eff, ct::Table<Enemy*>* et) : 
			Building(c), MagicEntity(eff) {
			enemyTable = et;
		}
		void update();
		buildingTypeEnum getType() const { return buildingTypeEnum::trap; }

	};
}


#endif