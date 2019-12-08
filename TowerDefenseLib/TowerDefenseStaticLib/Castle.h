#ifndef _CASTLE_H_
#define _CASTLE_H_

#include <string>

#include "Enums.h"
#include "Building.h"

namespace TD {
	class Castle : public Building {
	private:
		std::string title;
		double curHp;
		double maxHp;
		unsigned int money;
	public:
		Castle() : Building(), title("Castle"), curHp(100), maxHp(100), money(100) {}

		Castle(std::pair<double, double>* c, std::string t, double curhp, double maxhp, unsigned int money);

		void incHp(double v);
		void decHp(double v);
		inline void incMoney(unsigned int v) { money += v; }
		void decMoney(unsigned int v);
		
		inline double getCurHp() const { return curHp; }
		inline unsigned int getMoney() const { return money; }
		inline std::string getTitle() const { return title; }

		buildingTypeEnum getType() const { return buildingTypeEnum::castle; }

		void update() {}

		~Castle() {}

	};
}


#endif
