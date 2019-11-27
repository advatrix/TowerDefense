#include "pch.h"

#include <cmath>

#include "Tower.h"



namespace TD {
	Feature::Feature(int level, int price, double radius, double damage, double shotSpeed) {
		price_ = price;
		radius_ = radius;
		damage_ = damage;
		shotSpeed_ = shotSpeed;
		level_ = level;
	}

	DefaultTower::DefaultTower(Cell* cell, Feature* feature, Strategy* strategy, Landscape* ls) {
		cell_ = cell;
		feature_ = feature;
		strategy_ = strategy;
		land = ls;
		if (dynamic_cast<NearToTower*>(strategy)) strategyType_ = nearToTower;
		else if (dynamic_cast<NearToCastle*>(strategy)) strategyType_ = nearToCastle;
		else if (dynamic_cast<Weak*>(strategy)) strategyType_ = weak;
		else if (dynamic_cast<Strong*>(strategy)) strategyType_ = strong;
		else strategyType_ = fast;
	}

	void DefaultTower::fire(Enemy* e) {
		if (lastShot_ < feature_->shotSpeed()) {
			tick();
			return;
		}
		if (e) e->getHurt(feature_->damage());
		lastShot_ = 0;
	}

	DefaultTower::DefaultTower(Landscape* land) {
		strategy_ = land->strategies()[strategyTypeEnum::nearToTower];
		level_ = 0;
		lastShot_ = 0;
		feature_ = land->features()[level_];

	}

	DefaultTower::DefaultTower() {
		strategy_ = nullptr;
		level_ = 0;
		lastShot_ = 0;
		feature_ = nullptr;
	}

	void DefaultTower::attack() {
		if (strategy_) strategy_->attack(this);
		else throw std::runtime_error("this tower cannot attack");

	}

	void DefaultTower::upgrade() {
		level_++;
		feature_ = land->features()[level_];
		land->updateBalance(feature_->price());
		
	}

	double Strategy::distance(Enemy* e, Building* b) {
		std::pair<double, double> ce = e->cords(),
			cb = b->cords();
		return sqrt(pow((ce.first - cb.first), 2) - pow((ce.second - cb.second), 2));
	}

	void NearToTower::attack(Tower *tw) {
		Enemy* curEnemy = nullptr;
		double mind = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpDist = distance((*table)[i], tw);
			if (tmpDist < mind) {
				curEnemy = (*table)[i];
				mind = tmpDist;
			}
		}
		if (curEnemy && (mind < land->strategies()[tw->strategyType()]->radius()))
			tw->fire(curEnemy);
	}

	void NearToCastle::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double mind = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpDist = distance((*table)[i], land->castle);
			if (tmpDist < mind && distance((*table)[i], tw) < land->strategies()[tw->strategyType()]->radius() ){
				curEnemy = (*table)[i];
				mind = tmpDist;
			}
		}
		if (curEnemy && (mind < land->strategies()[tw->strategyType()]->radius()))
			tw->fire(curEnemy);
	}

	void Strong::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double maxf = 0;
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpf = (*table)[i]->hp();
			if (tmpf > maxf && distance((*table)[i], tw) < land->strategies()[tw->strategyType()]->radius()) {
				curEnemy = (*table)[i];
				maxf = tmpf;
			}
		}
		if (curEnemy) tw->fire(curEnemy);
	}

	void Weak::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double minf = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpf = (*table)[i]->hp();
			if (tmpf < minf && distance((*table)[i], tw) < land->strategies()[tw->strategyType()]->radius()) {
				curEnemy = (*table)[i];
				minf = tmpf;
			}
		}
		if (curEnemy) tw->fire(curEnemy);
	}

	void Fast::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double maxs = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmps = (*table)[i]->spd();
			if (tmps > maxs && distance((*table)[i], tw) < land->strategies()[tw->strategyType()]->radius()) {
				curEnemy = (*table)[i];
				maxs = tmps;
			}
		}
		if (curEnemy) tw->fire(curEnemy);
	}

	void Trap::attack() {
		EnemyTable* table = land->table();
		int size = table->size();
		for (int i = 0; i < size; i++) {
			std::pair<double, double> tmpCords = (*table)[i]->cords();
			std::pair<double, double> selfCords = cell_->cords();
			if (floor(tmpCords.first) == floor(selfCords.first) &&
				floor(tmpCords.second) == floor(selfCords.second)) {
				auto result = std::find(std::begin(attached), std::end(attached), (*table)[i]);
				if (result != std::end(attached)) {
					Enemy* en = (*table)[i];
					applyEffect(en);
					attached.push_back(en);
				}
			}
		}
	}

	void MagicEntity::applyEffect(Enemy* e) {
		if (e) e->addEffect(effect);
	}

	Trap::Trap() {
		land_ = nullptr;
		effect = nullptr;
		cell_ = nullptr;
	}

	Trap::Trap(Landscape* _land) {
		land_ = _land;
		effect = nullptr;
		cell_ = nullptr;
	}

	Trap::Trap(Landscape* _land, Cell* _cell, effectTypeEnum _type, int value, unsigned int time) {
		land_ = _land;
		cell_ = _cell;
		switch (_type) {
		case weakness: {
			effect = new Weakness(_type, value, time);
			break;
		}
		case slowdown: {
			effect = new Slowdown(_type, value, time);
			break;
		}
		case poison: {
			effect = new Poison(_type, value, time);
		}
		default: {
			throw std::invalid_argument("invalid effect type");
		}
		}
	}

	MagicTower::MagicTower() {
		land_ = nullptr;
		cell_ = nullptr;
		feature_ = nullptr;
		strategy_ = nullptr;
		effect = nullptr;
	}

	MagicTower::MagicTower(Landscape* _land, Cell* _cell, Feature* feature, Strategy* _strategy, effectTypeEnum _type, int _value, unsigned int _time) {
		land_ = _land;
		cell_ = _cell;
		feature_ = feature;
		strategy_ = _strategy;
		switch (_type) {
		case weakness: {
			effect = new Weakness(_type, value, time);
			break;
		}
		case slowdown: {
			effect = new Slowdown(_type, value, time);
			break;
		}
		case poison: {
			effect = new Poison(_type, value, time);
		}
		default: {
			throw std::invalid_argument("invalid effect type");
		}
		}
	}



	








}