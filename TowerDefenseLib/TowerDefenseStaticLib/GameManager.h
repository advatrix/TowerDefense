#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "Table.h"
#include "Landscape.h"
#include "Entity.h"

namespace ct = customTemplates;

namespace TD {
	class GameManager {
	private:
		Landscape* landscape;
		std::vector<Feature*> features;
		std::vector<Strategy*> strategies;

		std::vector<Entity*> entities;

		void update();
	public:
		int run(int level);
		void upgrade(int i, int j);
		void destroy(int i, int j);
		void save();
		void load(int level);

		void buildTower(int i, int j, unsigned int level);
		void buildMagicTower(int i, int j, unsigned int level, effectTypeEnum effType, unsigned int value, unsigned int time);
		void buildTrap(int i, int j, effectTypeEnum effType, unsigned int value);
		
		



	};
}



#endif