#include "pch.h"
#include "Enemy.h"

namespace TD {
	void Enemy::getHurt(double damage) {
		curHp -= damage * dmgMultiplier;
	}

	std::pair<double, double> Enemy::cords() const {
		return std::pair<double, double>(x_, y_);
	}

	void Enemy::setCords(std::pair<double, double> newCords) {
		x_ = newCords.first;
		y_ = newCords.second;
	}

	void Enemy::move() {
		directionEnum direction;
		if (road->getDist == 0) {
			hit(land_->getCastle());
			return;
		}
		std::pair<double, double> dest = road->getNext()->cords();
		std::pair<double, double> cur = road->cords();
		double deltaX = dest.first - cur.first;
		double deltaY = dest.second - cur.second;

		if (deltaY > 0) direction = east;
		if (deltaY < 0) direction = west;
		if (deltaX > 0) direction = south;
		if (deltaX < 0) direction = north;

		switch (direction) {
		case east: {
			y_ += realSpeed;
			break;
		}
		case west:{
			y_ -= realSpeed;
			break;
		}
		case south: {
			x_ += realSpeed;
			break;
		}
		case north: {
			x_ -= realSpeed;
			break;
		}
		}


	}

	void Enemy::calculateHp() {
		for (int i = 0; i < effects->getSize(); i++)
			effects[i].action(this);
	}

	Enemy::Enemy() {
		title = "Enemy";
		maxHp = 1;
		curHp = 1;
		money = 1;
		speed = 0.25;
		realSpeed = speed;
		effects = nullptr;
		road = nullptr;
		land_ = nullptr;
		x_ = -1;
		y_ = -1;
	}

	Enemy::Enemy(std::string _title, double _max, double _cur, int _money, double _speed, std::vector<Effect*> _effects, double _x, double _y, Landscape* land) {
		title = _title;
		maxHp = _max;
		curHp = _cur;
		money = _money;
		speed = _speed;
		realSpeed = speed;
		effects = new EffectTable;
		for (int i = 0; i < _effects.size(); i++) {
			effects->addEffect(_effects[i]);
		}
		land_ = land;
		road = land->getCell(floor(_x), floor(_y));
		x_ = road->cords().first;
		y_ = road->cords().second;
	}

	Effect* EffectTable::operator[] (int index) {
		if (index >= 0 && index < effectsVec.size()) return effectsVec[index];
		return nullptr;
	}

	void Enemy::turn() {
		move();
		calculateHp();
	}

	void Enemy::hit(Castle* c) {
		c->damage(curHp);
		c->updBalance(money);
	}

	void Enemy::addEffect(Effect* eff) {
		if (eff) effects->addEffect(eff);
	}

	EnemySchedule::EnemySchedule(std::multimap<unsigned int, Enemy*> sch) {
		schedule = sch;
	}

	std::vector<Enemy*> EnemySchedule::find(unsigned int time) {
		auto eqRange = schedule.equal_range(time);
		auto beg = eqRange.first;
		auto end = eqRange.second;
		std::vector<Enemy*> ret;
		for (auto it = beg; it != end; it++) {
			Enemy* tmp = (*it).second;
			ret.push_back(tmp);
		}
		return ret;
	}

	EffectTable::~EffectTable() {
		for (auto it = effectsVec.begin(); it != effectsVec.end(); it++)
			delete (*it);
	}

	void EffectTable::addEffect(Effect* eff) {
		if (eff) effectsVec.push_back(eff);
	}

	void Effect::update() {
		action();
		--remainedTime;
	}

	Effect::Effect() {
		value = 0;
		remainedTime = std::numeric_limits<unsigned int>::max();
		en = nullptr;
	}

	Effect::Effect(int _value, unsigned int _time, Enemy* e) {
		value = _value;
		remainedTime = _time;
		if (e) en = e;
		else throw std::invalid_argument("enemy nullptr");
	}

	void Weakness::action(Enemy* e) {
		e->dmgMultiplier *= ((100 + value) / 100);
	}

	void Slowdown::action(Enemy* e) {
		e->realSpeed /= (e->speed *(100 + value) / 100);
	}

	void Poison::action(Enemy* e) {
		e->curHp -= value;
	}







}
