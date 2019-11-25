#include "FileStructs.h"

namespace TD {
	FileCell::FileCell(int _x, int _y, int _type, int _building, int _buildingId) {
		x = _x;
		y = _y;
		type = _type;
		building = _building;
		buildingId = _buildingId;
	}

	FileTower::FileTower(int _x, int _y, int _towerType, int _effectId, int _level, int _strategytype, double _damage, double _radius, double _shotSpeed) {
		x = _x;
		y = _y;
		towerType = _towerType;
		effectId = _effectId;
	}

	FileLire::FileLire(int _x, int _y, int _enemiesCount) {
		x = _x;
		y = _y;
		enemiesCount = _enemiesCount;
	}

	FileScheduleItem::FileScheduleItem(unsigned int _time, std::string _name, double _maxHp, double _speed, int _money) {
		time = _time;
		name = _name;
		maxHp = _maxHp;
		speed = _speed;
		money = _money;
	}

	FileTrap::FileTrap(int _x, int _y, int _effectId) {
		x = _x;
		y = _y;
		effectId = _effectId;
	}

	FileCastle::FileCastle(int _x, int _y, int _money, std::string _title, double _maxHp, double _curHp) {
		x = _x;
		y = _y;
		money = _money;
		title = _title;
		maxHp = _maxHp;
		curHp = _curHp;
	}

	FileEffect::FileEffect(int _type, int _value, unsigned int _time) {
		type = _type;
		value = _value;
		time = _time;
	}

	FileEnemy::FileEnemy(std::string _name, double _cordX, double _cordY, double _maxHp, double _curHp,
		double _speed, int _money, int _nEffects) {
		name = _name;
		cord_x = _cordX;
		cord_y = _cordY;
		maxHp = _maxHp;
		curHp = _curHp;
		speed = _speed;
		money = _money;
		nEffects = _nEffects;
	}


}