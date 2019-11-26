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
		virtual ~Building() {}
		std::pair<double, double> cords() const;
	};

	class Castle : public Building {
	private:
		double curHp_;
		double maxHp_;
		int money_;
		std::string title_;
	public:
		Castle();
		inline double getHp() const { return curHp_; }
		inline std::string getTitle() const { return title_; }
		inline void damage(double quant) { curHp_ -= quant; }
		inline void updBalance(int income) { money_ += income; }
		Castle(Cell*, double curHp, double maxHp, int money, std::string title);

		friend class Landscape;

	};

	class Lire : public Building {
	private:
		EnemySchedule schedule;
	public:
		void spawn();
		void spawnByTime();
		Lire();
		~Lire();
		friend class Landscape;
	};
}

