#pragma once
#include "Landscape.h"
#include "Enemy.h"
#include "Tower.h"

namespace TD {
	class Building {
	protected:
		Cell* cell_;
	public:
		Building();
		Building(Cell*);
		~Building();
	};

	class Castle : Building {
	private:
		double curHp_;
		double maxHp_;
		int money_;
		std::string title_;
	public:
		Castle();
		inline double getHp() const { return curHp_; }
		inline std::string getTitle() const { return title_; }
		void damage(double);
		void updBalance(int);
		Castle(Cell*, double curHp, double maxHp, int money, std::string title);
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

