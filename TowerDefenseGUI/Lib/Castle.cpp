#include "pch.h"

#include <stdexcept>

#include "Castle.h"

namespace TD {
	Castle::Castle(std::pair<double, double> c, std::string t, double curhp, double maxhp, unsigned int _money) {
		if (curhp < 0) throw std::invalid_argument("negative current hp");
		if (curhp > maxhp) throw std::invalid_argument("current hp are greater than max hp");

		cords = c;
		title = t;
		curHp = curhp;
		maxHp = maxhp;
		money = _money;
	}

	void Castle::incHp(double v) {
		v = abs(v);
		if (v + curHp > maxHp) curHp = maxHp;
		else curHp += v;
	}

	void Castle::decHp(double v) {
		v = abs(v);
		if (curHp < v) curHp = 0;
		else curHp -= v;
	}

	void Castle::decMoney(unsigned int v) {
		if (money < v) throw std::runtime_error("not enough money");
		money -= v;
	}
}
