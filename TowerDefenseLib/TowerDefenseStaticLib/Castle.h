/**
\file 
\brief This file contains representation of the Castle class
*/

#ifndef _CASTLE_H_
#define _CASTLE_H_

#include <string>

#include "Enums.h"
#include "Building.h"

namespace TD {
	/**
	\brief This class describes Castle
	This class describes Castle which is the main building in the entire game.
	*/
	class Castle : public Building {
	private:
		std::string title;
		double curHp;
		double maxHp;
		unsigned int money;
	public:
		Castle() : Building(), title("Castle"), curHp(100), maxHp(100), money(100) {}

		Castle(std::pair<double, double> c, std::string t, double curhp, double maxhp, unsigned int _money);
	
		/**
		Increments hit points of the castle
		\param [in] v Hit points to increment by
		*/
		void incHp(double v);

		/**
		Decrements hit points of the castle or sets it to zero if the result of decrementing is negative.
		\param [in] v Hit points to decrement by
		*/
		void decHp(double v);

		/**
		Increments money balance of the castle
		\param [in] v Money to increment by
		*/
		inline void incMoney(unsigned int v) { money += v; }

		/**
		Decrement money balance of the castle or sets it to zero if the result of decrementing is negative
		\param [in] v Money to decrement by		
		*/
		void decMoney(unsigned int v);
		
		/**
		Returns current hit points of the castle
		\return current hit points of the castle
		*/
		inline double getCurHp() const { return curHp; }

		/**
		Returns the maximum possible hit points the castle can have
		\return the maximum possible hit points
		*/
		inline double getMaxHp() const { return maxHp; }

		/**
		Returns current money balance of the castle
		\return current money balance
		*/
		inline unsigned int getMoney() const { return money; }

		/**
		Returns title of the castle
		\return title of the castle
		*/
		inline std::string getTitle() const { return title; }

		/**
		Reimplemention of the getType() function from parent Building class.
		\return Type "Castle" as buildingTypeEnum element
		*/
		buildingTypeEnum getType() const { return buildingTypeEnum::castle; }

		/**
		\warning Not implemented yet
		*/
		void update() {}

		inline void setMaxHp(double newHp) { if (newHp > maxHp) maxHp = newHp; }

		~Castle() {}

	};
}


#endif
