#pragma once
#include "Landscape.h"
#include "Enemy.h"
#include "Tower.h"

namespace TD {
	class Building {
	protected:
		Cell* cell;
	public:
		Building();
		Building(Cell*);
		~Building();
	};

	class Castle : Building {
	private:
		double curHp;
		double maxHp;
		int money;
		std::string title;
	public:
		Castle();
		std::string getTitle() const;
		void damage(double);
		void updBalance(int);
	};

	class Lire : Building {
	private:
		EnemySchedule schedule;
	public:
		void spawn();
		void spawnByTime();
		Lire();
		~Lire();
	};
}

