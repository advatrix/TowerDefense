#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Table.h"

#include "Entity.h"

namespace ct = customTemplates;

namespace TD {

	class Effect;

	class Enemy {
	private:
		double x;
		double y;
		double maxHp;
		double curHp;
		double curSpeed;
		double maxSpeed;
		double dmgMultiplier;
		bool alive;
		int money;
		ct::Table<Effect*> effects;
		std::string title;
	public:
		inline std::string getTitle() const { return title; }
		inline std::pair<double, double> getCords() const { return std::pair<double, double>(x, y); }
		inline double getCurHp() const { return curHp; }
		inline int getMoney() const { return money; }
		inline double getDamageMultiplier() const { return dmgMultiplier; }
		inline double getCurSpeed() const { return curSpeed; }

		inline void mulDamageMultiplier(double v) { dmgMultiplier *= v; }
		inline void divDamageMultiplier(double v) { dmgMultiplier /= v; }

		inline void mulCurrentSpeed(double v) { curSpeed *= v; }
		inline void divCurrentSpeed(double v) { curSpeed /= v; }




		Enemy() :
			x(-1), y(-1), maxHp(1), curHp(1), maxSpeed(0), curSpeed(0), dmgMultiplier(1), money(0), effects(),
			title("empty"), alive(false) {}

		Enemy(double _x, double _y, double _maxHp, double maxSpeed, int money, std::string& title,
			double _curHp = -1, double _curSpeed = -1, double dmgMultiplier = 1, ct::Table<Effect*> _effects = ct::Table<Effect*>(), 
			bool isAlive = false);

		void move(double deltaX, double deltaY);
		void place(std::pair<double, double>& c);

		inline void makeDamage(double dmg) { curHp -= dmg; }
		inline void addEffect(Effect* e) { effects.insert(e); }

		inline bool isAlive() const { return alive; }
		inline void revive() { alive = true; }
		inline void kill() { alive = false; }
	};
}

#endif _ENEMY_H_
