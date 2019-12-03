#include "pch.h"
#include "Enemy.h"

namespace TD {
	Enemy::Enemy(double _x, double _y, double _maxHp, double _maxSpeed, int _money, std::string& _title,
		double _curHp = -1, double _curSpeed = -1, double _dmgMultiplier = 1, ct::Table<Effect*> _effects = ct::Table<Effect*>(), 
		bool isAlive) {
	
		if (maxSpeed <= 0) throw std::invalid_argument("illegal max speed");
		if (maxHp <= 0) throw std::invalid_argument("illegal max hp");

		x = _x;
		y = _y;
		maxSpeed = _maxSpeed;
		money = _money;
		title = _title;
		maxHp = _maxHp;

		if (_curHp <= 0) curHp = maxHp;
		else curHp = _curHp;

		if (_curSpeed <= 0) curSpeed = maxSpeed;
		else curSpeed = _curSpeed;

		dmgMultiplier = _dmgMultiplier;
		effects = _effects;

		alive = isAlive;
	}

	void Enemy::move(double deltaX, double deltaY) {
		x += deltaX;
		y += deltaY;
	}

	void Enemy::move(std::pair<double, double>& c) {
		x = c.first;
		y = c.second;
	}
}
