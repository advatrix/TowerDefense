#include "pch.h"
#include "Building.h"

namespace TD {
	Castle::Castle(Cell* cell, double curHp, double maxHp, int money, std::string title) {
		cell_ = cell;
		curHp_ = curHp;
		maxHp_ = maxHp;
		money_ = money;
		title_ = title;
	}

	Building::Building() {
		cell_ = nullptr;
	}

	Building::Building(Cell* cell) {
		cell_ = cell;
	}

	Castle::Castle() {
		curHp_ = 100;
		maxHp_ = 100;
		money_ = 100;
		title_ = "Castle";
	}

	std::pair<double, double> Building::cords() const {
		return cell_->cords();
	}

	Lire::Lire() {
		cell_ = nullptr;
		schedule = nullptr;
		land = nullptr;
	}

	Lire::Lire(Cell* _cell, EnemySchedule* _schedule, Landscape* _land) {
		cell_ = _cell;
		schedule = _schedule;
		land = _land;
	}

	void Lire::spawn(Enemy* en) {
		EnemyTable* table = land->enemyTable;
		en->setCords(cell_->cords());
		table->add(en);
	}

	void Lire::spawnByTime() {
		std::vector<Enemy*> enemies = schedule->find(land->time);
		for (auto it = enemies.begin(); it != enemies.end(); it++) spawn(*it);
	}

	


	

}
