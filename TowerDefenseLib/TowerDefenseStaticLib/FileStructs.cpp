#include "pch.h"
#include "FileStructs.h"

namespace TD {
	FileCell::FileCell(int _x, int _y, int _type, int _building, int _buildingId) {
		x = _x;
		y = _y;
		type = _type;
		building = _building;
		buildingId = _buildingId;
	}

	FileTower::FileTower(int _x, int _y, int _towerType, int _effectId, int _level, int _strategytype) {
		x = _x;
		y = _y;
		towerType = _towerType;
		effectId = _effectId;
		level = _level;
		strategyType = _strategytype;
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

	FileFeature::FileFeature(int _level, int _price, double _damage, double _radius, double _shotSpeed) {
		level = _level;
		price = _price;
		damage = _damage;
		radius = _radius;
		shotSpeed = _shotSpeed;
	}


	std::ostream& operator<< (std::ostream& o, const FileCell& f) {
		o << f.x << std::endl << f.y << std::endl << f.type << std::endl << f.building << std::endl << f.buildingId << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileCell& f) {
		i >> f.x >> f.y >> f.type >> f.building >> f.buildingId;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileTower& f) {
		o  << f.x << std::endl << f.y << std::endl << f.towerType << std::endl << f.effectId << std::endl << f.level << std::endl << f.strategyType << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileTower& f) {
		i >> f.x >> f.y >> f.towerType >> f.effectId >> f.level >> f.strategyType;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileLire& f) {
		o << f.x << std::endl << f.y << std::endl << f.enemiesCount << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileLire& f) {
		i >> f.x >> f.y >> f.enemiesCount;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileScheduleItem& f) {
		o << f.time << std::endl << f.name << std::endl << f.maxHp << std::endl << f.speed << std::endl << f.money << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileScheduleItem& f) {
		i >> f.time >> f.name >> f.maxHp >> f.speed >> f.money;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileTrap& f) {
		o << f.x << std::endl << f.y << std::endl << f.effectId << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileTrap& f) {
		i >> f.x >> f.y >> f.effectId;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileCastle& f) {
		o << f.x << std::endl << f.y << std::endl << f.money << std::endl << f.title << std::endl << f.maxHp << std::endl << f.curHp << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileCastle& f) {
		i >> f.x >> f.y >> f.money >> f.title >> f.maxHp >> f.curHp;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileEffect& f) {
		o << f.type << std::endl << f.value << std::endl << f.time << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileEffect& f) {
		i >> f.type >> f.value >> f.time;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileEnemy& f) {
		o << f.name << std::endl << f.cord_x << std::endl << f.cord_y << std::endl << f.maxHp << std::endl << f.curHp << std::endl << f.speed << std::endl << f.money << std::endl << f.nEffects << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileEnemy& f) {
		i >> f.name >> f.cord_x >> f.cord_y >> f.maxHp >> f.curHp >> f.speed >> f.money >> f.nEffects;
		return i;
	}


	std::ostream& operator<< (std::ostream& o, const FileFeature& f) {
		o << f.level << std::endl << f.price << std::endl << f.damage << std::endl << f.radius << std::endl << f.shotSpeed << std::endl;
		return o;
	}

	std::istream& operator >> (std::istream& i, FileFeature& f) {
		i >> f.level >> f.price >> f.damage >> f.radius >> f.shotSpeed;
		return i;
	}
}
