/**
\file
This file contains implementation of all classes describing Tower's strategies.
*/

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "Enums.h"
#include "Enemy.h"

namespace ct = customTemplates;

namespace TD {

	/**
	Provides polymorphism for every strategy used in the game
	*/
	class Strategy {
	protected:
		ct::Table<Enemy*>* enemyTable; ///< A pointer to the table of the enemies on the map
	public: 
		virtual ~Strategy() {}
		virtual inline strategyTypeEnum getType() const { return strategyTypeEnum::noStrategy; }

		/**
		Calculates the distance between two points on the map
		\param [in] a Cords of the first point as std::pair
		\param [in] b Cords of the second point as std::pair
		*/
		static double distance(std::pair<double, double> a, std::pair<double, double> b);

		/**
		Defines a target Enemy for the Tower to attack
		\param [in] cords Cords of the Tower as std::pair
		\param [in] radius Radius of the Tower's Feature
		\return A pointer to the Enemy Tower should attack
		*/
		virtual Enemy* getTarget(std::pair<double, double>& cords, double raduis) const = 0;
		Strategy(): enemyTable(nullptr) {}
		Strategy(ct::Table<Enemy*>* _enemyTable);
	};

	/**
	Describes "The nearest to the Tower" strategy
	*/
	class NearToTower : public Strategy {
	public:
		/**
		Defines a target Enemy for the Tower to attack: the nearest one to the Tower within its Feature radius
		\param [in] cords Cords of the Tower as std::pair
		\param [in] radius Radius of the Tower's Feature
		\return A pointer to the Enemy Tower should attack
		*/
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		NearToTower() {
			enemyTable = nullptr;
		}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::nearToTower; }

		NearToTower(ct::Table<Enemy*>* _enemyTable);
		~NearToTower() {}
	};

	/**
	This class describes "the nearest to the Castle" strategy
	*/
	class NearToCastle : public Strategy {
	private:
		std::pair<double, double> castleCords; ///< Cords of the Castle s std::pair
	public:
		/**
		Defines a target Enemy for the Tower to attack: the nearest one to the Castle within Feature radius of the Tower
		\param [in] cords Cords of the Tower as std::pair
		\param [in] radius Radius of the Tower's Feature
		\return A pointer to the Enemy Tower should attack
		*/
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		NearToCastle() {
			enemyTable = nullptr;
		}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::nearToCastle; }

		NearToCastle(ct::Table<Enemy*>* enemyTable, std::pair<double, double> _castleCords) :
			Strategy(enemyTable), castleCords(_castleCords)
		{}

		~NearToCastle() {}
	};
	
	/**
	This class describes "The strongest" strategy
	*/
	class Strong : public Strategy {
	public:
		/**
		Defines a target Enemy for the Tower to attack: Enemy with the most hit points within the Feature radius of the Tower
		\param [in] cords Cords of the Tower as std::pair
		\param [in] radius Radius of the Tower's Feature
		\return A pointer to the Enemy Tower should attack
		*/
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Strong() {
			enemyTable = nullptr;
		}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::strong; }

		Strong(ct::Table<Enemy*>* _enemyTable);
		~Strong() {}
	};

	/**
	This class describes "The weakest" strategy
	*/
	class Weak : public Strategy {
	public:
		/**
		Defines a target Enemy for the Tower to attack: the Enemy with the least hit points within the Feature radius of the Tower
		\param [in] cords Cords of the Tower as std::pair
		\param [in] radius Radius of the Tower's Feature
		\return A pointer to the Enemy Tower should attack
		*/
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Weak() {
			enemyTable = nullptr;
		}

		Weak(ct::Table<Enemy*>* _enemyTable);
		~Weak() {}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::weak; }
	};

	/**
	This class describes "The fasteft" strategy
	*/
	class Fast : public Strategy {
	public:
		/**
		Defines a target Enemy for the Tower to attack: the one with the most current speed within the radius of the Feature of the Tower
		\param [in] cords Cords of the Tower as std::pair
		\param [in] radius Radius of the Tower's Feature
		\return A pointer to the Enemy Tower should attack
		*/
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Fast() {
			enemyTable = nullptr;
		}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::fast; }

		Fast(ct::Table<Enemy*>* _enemyTable);
		~Fast() {}
	};
}


#endif