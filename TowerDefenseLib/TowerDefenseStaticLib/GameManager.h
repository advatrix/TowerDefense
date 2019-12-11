#pragma warning(disable:4996)

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_


#include "Table.h"
#include "Landscape.h"
#include "Entity.h"

namespace ct = customTemplates;

namespace TD {
	class GameManager {
	private:
		unsigned int level;
		Landscape* landscape;
		std::vector<Feature*> features;
		std::vector<Strategy*> strategies;

		std::vector<Entity*> entities;

		
	public:
		void update();
		GameManager(unsigned int _level) {
			load(_level);
			level = _level;
		}

		GameManager(std::string fname) {
			load(fname);
			level = 0;
		}

		GameManager(): features(), strategies(), entities() {
			landscape = nullptr;
			level = 0;
		}

		~GameManager();


		void upgrade(int i, int j);
		void destroy(int i, int j);
		void save();
		void load(unsigned int level);
		void load(std::string);

		void buildTower(int i, int j, unsigned int level);
		void buildMagicTower(int i, int j, unsigned int level, effectTypeEnum effType, unsigned int value, unsigned int time);
		void buildTrap(int i, int j, effectTypeEnum effType, unsigned int value, unsigned int time);
		
		inline ct::Table<Enemy*>* getEnemyTable() const { return landscape->getEnemyTable(); }
		inline double getHp() const { return landscape->getCastle()->getCurHp(); }
		inline int getMoney() const { return landscape->getCastle()->getMoney(); }



	};
}



#endif