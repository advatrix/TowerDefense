#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "Enums.h"
#include "Enemy.h"

namespace ct = customTemplates;

namespace TD {


	class Strategy {
	protected:
		ct::Table<Enemy*>* enemyTable;
	public: 
		virtual ~Strategy() {}
		virtual inline strategyTypeEnum getType() const { return strategyTypeEnum::noStrategy; }
		static double distance(std::pair<double, double>, std::pair<double, double>);
		virtual Enemy* getTarget(std::pair<double, double>& cords, double raduis) const = 0;
		Strategy(): enemyTable(nullptr) {}
		Strategy(ct::Table<Enemy*>* _enemyTable);
	};

	class NearToTower : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		NearToTower() {
			enemyTable = nullptr;
		}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::nearToTower; }

		NearToTower(ct::Table<Enemy*>* _enemyTable);
		~NearToTower() {}
	};

	class NearToCastle : public Strategy {
	private:
		std::pair<double, double> castleCords;
	public:
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

	class Strong : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Strong() {
			enemyTable = nullptr;
		}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::strong; }

		Strong(ct::Table<Enemy*>* _enemyTable);
		~Strong() {}
	};

	class Weak : public Strategy {
	public:
		Enemy* getTarget(std::pair<double, double>& cords, double raduis) const;

		Weak() {
			enemyTable = nullptr;
		}

		Weak(ct::Table<Enemy*>* _enemyTable);
		~Weak() {}

		inline strategyTypeEnum getType() const { return strategyTypeEnum::weak; }
	};

	class Fast : public Strategy {
	public:
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