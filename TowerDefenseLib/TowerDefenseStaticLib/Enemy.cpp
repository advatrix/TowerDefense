#include "pch.h"
#include "Enemy.h"

namespace TD {
	void Enemy::getHurt(double damage) {
		curHp -= damage;
	}

	std::pair<double, double> Enemy::cords() const {
		return std::pair<double, double>(x_, y_);
	}
}
