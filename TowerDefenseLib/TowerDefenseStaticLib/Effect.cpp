#include "pch.h"
#include "Effect.h"

namespace TD {
	Effect::Effect(Enemy* _en, unsigned int time, unsigned int val) {
		enemy = _en;
		remainedTime = time;
		value = val;
		active = false;
	}

	void Weakness::update() {
		if (!active) {
			enemy->mulDamageMultiplier(pc(value));
			active = true;
		}
		if (--remainedTime == 0) {
			enemy->divDamageMultiplier(pc(value));
			active = false;
		}
	}

	void Slowdown::update() {
		if (!active) {
			enemy->divCurrentSpeed(pc(value));
			active = true;
		}
		if (--remainedTime == 0) {
			enemy->mulCurrentSpeed(pc(value));
			active = false;
		}
	}

	void Poison::update() {
		if (!active) active = true;
		enemy->makeDamage(value);
		if (--remainedTime == 0) active = false;
	}

	Effect* Weakness::copy() {
		Effect* ret = new Weakness(enemy, remainedTime, value);
		return ret;
	}

	Effect* Slowdown::copy() {
		Effect* ret = new Slowdown(enemy, remainedTime, value);
		return ret;
	}

	Effect* Poison::copy() {
		Effect* ret = new Poison(enemy, remainedTime, value);
		return ret;
	}
}
