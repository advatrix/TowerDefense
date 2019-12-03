#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "Enums.h"
#include "Enemy.h"

namespace ct = customTemplates;

namespace TD {


	class Strategy {
	protected:
		static const strategyTypeEnum type;
		ct::Table<Enemy*>* enemyTable;
	public:
		virtual Enemy* getTarget(std::pair<double, double>& cords) const = 0; 
		virtual ~Strategy() {}
		inline strategyTypeEnum getType() const { return type; }
		static double distance(std::pair<double, double>, std::pair<double, double>);
		virtual Enemy* getTarget(std::pair<double, double>& cords, double raduis) const = 0;
		Strategy(): enemyTable(nullptr) {}
		Strategy(ct::Table<Enemy*>* _enemyTable);
	};

	class NearToTower : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;


		NearToTower() {}
		~NearToTower() {}
	};

	class NearToCastle : public Strategy {
	private:
		std::pair<double, double> castleCords;
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		NearToCastle() {}
		NearToCastle(ct::Table<Enemy*>* enemyTable, std::pair<double, double> _castleCords) :
			Strategy(enemyTable), castleCords(castleCords) {}
		~NearToCastle() {}
	};

	class Strong : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Strong() {}
		~Strong() {}
	};

	class Weak : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Weak() {}
		~Weak() {}
	};

	class Fast : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Fast() {}
		~Fast() {}
	};
}


#endif