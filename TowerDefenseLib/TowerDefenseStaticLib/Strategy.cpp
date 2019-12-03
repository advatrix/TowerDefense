#include "pch.h"

#include <cmath>

#include "Strategy.h"

namespace TD {
	const strategyTypeEnum Strategy::type = noStrategy;
	const strategyTypeEnum NearToTower::type = nearToTower;
	const strategyTypeEnum NearToCastle::type = nearToCastle;
	const strategyTypeEnum Strong::type = strong;
	const strategyTypeEnum Weak::type = weak;
	const strategyTypeEnum Fast::type = fast;

	Strategy::Strategy(ct::Table<Enemy*>* _enemyTable) {
		if (!_enemyTable) throw std::invalid_argument("enemyTable nullptr");
		enemyTable = _enemyTable;
	}


	double Strategy::distance(std::pair<double, double>a, std::pair<double, double>b) {
		return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
	}

	Enemy* NearToTower::getTarget(std::pair<double, double>& cords, double radius) const {
		Enemy* curEnemy = nullptr;
		double mind = radius;
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			std::pair<double, double> enemyCords = (*it)->getCords();
			double curDist = distance(cords, enemyCords);
			if (curDist < mind) {
				mind = curDist;
				curEnemy = (*it);
			}
		}
		return curEnemy;
	}

	Enemy* NearToCastle::getTarget(std::pair<double, double>& cords, double radius) const {
		Enemy* curEnemy = nullptr;
		double mind = std::numeric_limits<double>::max();
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			std::pair<double, double> enemyCords = (*it)->getCords();
			double castleDist = distance(castleCords, enemyCords);
			double towerDist = distance(cords, enemyCords);
			if (castleDist < mind && towerDist <= radius) {
				mind = castleDist;
				curEnemy = (*it);
			}
		}
		return curEnemy;
	}

	Enemy* Strong::getTarget(std::pair<double, double>& cords, double radius) const {
		Enemy* curEnemy = nullptr;
		double maxStrength = 0;
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			std::pair<double, double> enemyCords = (*it)->getCords();
			double towerDist = distance(cords, enemyCords);
			double currStrength = (*it)->getCurHp();
			if (currStrength > maxStrength && towerDist <= radius) {
				maxStrength = currStrength;
				curEnemy = (*it);
			}
		}
		return curEnemy;
	}

	Enemy* Weak::getTarget(std::pair<double, double>& cords, double radius) const {
		Enemy* curEnemy = nullptr;
		double minStrength = 0;
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			std::pair<double, double> enemyCords = (*it)->getCords();
			double towerDist = distance(cords, enemyCords);
			double currStrength = (*it)->getCurHp();
			if (currStrength < minStrength && towerDist <= radius) {
				minStrength = currStrength;
				curEnemy = (*it);
			}
		}
		return curEnemy;
	}

	Enemy* Fast::getTarget(std::pair<double, double>& cords, double radius) const {
		Enemy* curEnemy = nullptr;
		double maxSpeed = 0;
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			std::pair<double, double> enemyCords = (*it)->getCords();
			double towerDist = distance(cords, enemyCords);
			double currSpeed = (*it)->getCurSpeed();
			if (currSpeed > maxSpeed && towerDist <= radius) {
				maxSpeed = currSpeed;
				curEnemy = (*it);
			}
		}
		return curEnemy;
	}

	
	
}
