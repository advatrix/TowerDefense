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

	DefaultTower::DefaultTower(Feature* feature, Strategy* strategy, Landscape* ls) {
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
		if (lastShot_ < feature_->shotSpeed()) return;
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

	void Strong::attack(Tower* tw) {
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

	








}