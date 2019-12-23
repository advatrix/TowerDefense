/**
\file
\brief This file describes Enemy class
*/
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Table.h"

#include "Entity.h"

namespace ct = customTemplates;

namespace TD {

	class Effect;
	/**
	\brief This class decribes every Enemy in the game
	*/
	class Enemy {
	private:
		double x;///<Current X coordinate of the enemy
		double y;///<Current Y coordinate of the enemy
		double maxHp;///<Maximum possible hit points of the enemy
		double curHp;///<Current hit points of the enemy
		double curSpeed;
		double maxSpeed;
		double dmgMultiplier;///<All damage made on enemy is multiplied by this 
		bool alive;///<Flag that shows if the enemy is active
		int money;///<Money count the Castle will get for killing the enemy
		ct::Table<Effect*> effects;///<Table of effects affecting the enemy in current time
		std::string title;///<Title of the enemy
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

		inline ct::Table<Effect*> getEffects() const { return effects; }




		Enemy() :
			x(-1), y(-1), maxHp(1), curHp(1), maxSpeed(0), curSpeed(0), dmgMultiplier(1), money(0), effects(),
			title("empty"), alive(false) {}

		Enemy(double _x, double _y, double _maxHp, double maxSpeed, int money, std::string& title,
			double _curHp = -1, double _curSpeed = -1, double dmgMultiplier = 1, ct::Table<Effect*> _effects = ct::Table<Effect*>(), 
			bool isAlive = false);
		/**
		\brief Moves enemy in current direction
		Changes Enemy's cords on deltas multiplied by current enemy's speed
		\param [in] deltaX direction on X axe
		\param [in] deltaY direction on Y axe
		*/
		void move(double deltaX, double deltaY);

		/**
		Places the enemy on current position on the game level
		\param [in] c std::pair from x and y coordinates to place the enemy
		*/
		void place(std::pair<double, double> c);

		/**
		\brief Makes damage on the enemy
		Substracts dmg multiplied by dmgMultiplier from current hit points
		\param [in] dmg Raw damage value
		*/
		inline void makeDamage(double dmg) { curHp -= (dmg * dmgMultiplier); }

		/**
		\brief Adds new effect affecting the enemy
		Inserts a pointer to the new effect to the enemy's effects table
		\param [in] e Pointer to the new effect
		*/
		inline void addEffect(Effect* e) { effects.insert(e); }

		inline bool isAlive() const { return alive; }

		/**
		Sets the "alive" flag to true making enemy active
		*/
		inline void revive() { alive = true; }

		/**
		Sets the "alive" flag to false making enemy inactive
		*/
		inline void kill() { alive = false; }
	};
}

#endif _ENEMY_H_
