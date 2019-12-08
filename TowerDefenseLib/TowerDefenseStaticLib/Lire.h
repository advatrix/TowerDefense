#ifndef _LIRE_H_
#define _LIRE_H_

#include <map>

#include "Table.h"
#include "Building.h"
#include "Enemy.h"


namespace TD {
	class Lire : public Building {
	private:
		std::multimap<unsigned int, Enemy*> schedule;
		customTemplates::Table<Enemy*>* enemyTable;
		unsigned int internalTime;

		friend class GameManager;
		inline const std::multimap<unsigned int, Enemy*>& getSchedule() { return schedule; }

	public:
		Lire() : Building(), schedule(), internalTime(0), enemyTable(nullptr) {}
		Lire(std::pair<double, double> c, std::multimap<unsigned int, Enemy*> sch, 
			unsigned int t, customTemplates::Table<Enemy*>* et) {
			cords = c;
			schedule = sch;
			internalTime = t;
			enemyTable = et;
		}

		void update();
		void spawn(Enemy*);
		void spawn();

		inline buildingTypeEnum getType() const { return buildingTypeEnum::lire; }
	};
}

#endif