/**
This file contains implementation of the Lire class
*/
#ifndef _LIRE_H_
#define _LIRE_H_

#include <map>

#include "Table.h"
#include "Building.h"
#include "Enemy.h"


namespace TD {
	/**
	This class describes states of the lires, which spawn enemies according to their schedule.
	*/
	class Lire : public Building {
	private:
		std::multimap<unsigned int, Enemy*> schedule; ///< Schedule of the enemies to spawn: <time of spawn, pointer to the Enemy to spawn
		customTemplates::Table<Enemy*>* enemyTable; ///< A pointer to the table of Enemies that are active now on the map
		unsigned int internalTime; ///< Internal time according to which the enemies spawn

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

		/**
		Updates state of the Lire: increments internal time and spawns enemies if necessary
		*/
		void update();

		/**
		Spawns current Enemy disregarging the schedule
		\param [in] e A pointer to the enemy to spawn
		*/
		void spawn(Enemy* e);

		/**
		Spawns enemies according to internal lire's schedule if neccesary
		*/
		void spawn();

		inline buildingTypeEnum getType() const { return buildingTypeEnum::lire; }
	};
}

#endif