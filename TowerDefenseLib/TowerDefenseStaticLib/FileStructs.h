#ifndef _FILESTRUCTS_H_
#define _FILESTRUCTS_H_

#include <iostream>

#include "Enums.h"


namespace TD {
	struct FileCell {
		int x;
		int y;
		int type;
		int building;
		int buildingId;
		FileCell() : x(0), y(0), type(forest), building(none), buildingId(0) {}
		FileCell(int _x, int _y, int _type, int _building, int _buildingId);

		friend std::ostream& operator << (std::ostream&, const FileCell&);
		friend std::istream& operator >> (std::istream&, FileCell&);

	};

	struct FileTower {
		int x;
		int y;
		int towerType;
		int effectId;
		int level;
		int strategyType;
		FileTower() : x(0), y(0), towerType(default_), effectId(0), level(1), strategyType(nearToTower) {}
		FileTower(int _x, int _y, int _towerType, int _effectId, int _level, int _strategytype);

		friend std::ostream& operator << (std::ostream&, const FileTower&);
		friend std::istream& operator >> (std::istream&, const FileTower&);
	};

	struct FileLire {
		int x;
		int y;
		int enemiesCount;
		FileLire() : x(0), y(0), enemiesCount(0) {}
		FileLire(int _x, int _y, int _enemiesCount);

		friend std::ostream& operator << (std::ostream&, const FileLire&);
		friend std::istream& operator >> (std::istream&, const FileLire&);
	};

	struct FileScheduleItem {
		unsigned int time;
		std::string name;
		double maxHp;
		double speed;
		int money;
		FileScheduleItem() : time(0), name("Enemy"), maxHp(1), speed(0), money(0) {}
		FileScheduleItem(unsigned int _time, std::string _name, double _maxHp, double _speed, int _money);

		friend std::ostream& operator << (std::ostream&, const FileScheduleItem&);
		friend std::istream& operator >> (std::istream&, const FileScheduleItem&);
	};

	struct FileTrap {
		int x;
		int y;
		int effectId;
		FileTrap() : x(0), y(0), effectId(0) {}
		FileTrap(int _x, int _y, int _effectId);

		friend std::ostream& operator << (std::ostream&, const FileTrap&);
		friend std::istream& operator >> (std::istream&, const FileTrap&);
	};

	struct FileCastle {
		int x;
		int y;
		int money;
		std::string title;
		double maxHp;
		double curHp;
		FileCastle() : x(0), y(0), money(0), title("Castle"), maxHp(1), curHp(1) {}
		FileCastle(int _x, int _y, int _money, std::string _title, double _maxHp, double _curHp);

		friend std::ostream& operator << (std::ostream&, const FileCastle&);
		friend std::istream& operator >> (std::istream&, const FileCastle&);
	};

	struct FileEffect {
		int type;
		int value;
		unsigned int time;
		FileEffect() : type(poison), value(0), time(0) {}
		FileEffect(int _type, int _value, unsigned int _time);

		friend std::ostream& operator << (std::ostream&, const FileEffect&);
		friend std::istream& operator >> (std::istream&, const FileEffect&);
	};

	struct FileEnemy {
		std::string name;
		double cord_x;
		double cord_y;
		double maxHp;
		double curHp;
		double speed;
		int money;
		int nEffects;
		FileEnemy() : name("Enemy"), cord_x(0), cord_y(0), maxHp(1), curHp(1), speed(1), money(0),
			nEffects(0) {}
		FileEnemy(std::string _name, double _cordX, double _cordY, double _maxHp, double _curHp,
			double _speed, int _money, int _nEffects);

		friend std::ostream& operator << (std::ostream&, const FileEnemy&);
		friend std::istream& operator >> (std::istream&, const FileEnemy&);
	};

	struct FileFeature {
		int level;
		int price;
		double damage;
		double radius;
		double shotSpeed;
		FileFeature() : level(1), price(1), damage(1), radius(1), shotSpeed(1) {}
		FileFeature(int _level, int _price, double _damage, double _radius, double _shotSpeed);

		friend std::ostream& operator << (std::ostream&, const FileFeature&);
		friend std::istream& operator >> (std::istream&, const FileFeature&);
	};
}

#endif

