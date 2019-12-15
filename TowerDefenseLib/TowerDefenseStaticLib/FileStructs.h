/**
\file
This file contains implementation of all structures used to work with configuration files
*/
#ifndef _FILESTRUCTS_H_
#define _FILESTRUCTS_H_

#include <iostream>

#include "Enums.h"


namespace TD {
	/**
	This structure describes Cell state in the configuration file
	*/
	struct FileCell {
		int x; ///< X cord of the Cell
		int y; ///< Y cord of the Cell
		int type; ///< Type of the Cell according to cellTypeEnum
		int building; ///< Type of the Building according to buildingTypeEnum.
		int buildingId; ///< Index of the particular building in the corresponding file, or zero if no building
		FileCell() : x(0), y(0), type(forest), building(none), buildingId(0) {}
		FileCell(int _x, int _y, int _type, int _building, int _buildingId);

		friend std::ostream& operator << (std::ostream&, const FileCell&);
		friend std::istream& operator >> (std::istream&, FileCell&);

	};


	/**
	This structure describes Tower state in the configuration file
	*/
	struct FileTower {
		int x; ///< X cord of the Cell the Tower stands on
		int y; ///< Y cord of the Cell the Tower stants on
		int towerType; ///< Type of the Tower according to buildingTypeEnum (default or magic)
		int effectId; ///< Index of the Effect Tower applies on the enemies in the corresponding file or zero if the Tower is not magic
		int level; ///< Level of the tower (index of the Feature Tower has)
		int strategyType; ///< Type of the attack Strategy Tower has according to strtegytypeEnum
		FileTower() : x(0), y(0), towerType(default_), effectId(0), level(1), strategyType(nearToTower) {}
		FileTower(int _x, int _y, int _towerType, int _effectId, int _level, int _strategytype);

		friend std::ostream& operator << (std::ostream&, const FileTower&);
		friend std::istream& operator >> (std::istream&, FileTower&);
	};

	/**
	This structure describes Lire state in the configuration file
	*/
	struct FileLire {
		int x; ///< X cord of the Cell the Lire stands on
		int y; ///< Y cord of the Cell the Lire stands on
		int enemiesCount; ///< Count of the Enemies the Lire hasn't spawned yet
		FileLire() : x(0), y(0), enemiesCount(0) {}
		FileLire(int _x, int _y, int _enemiesCount);

		friend std::ostream& operator << (std::ostream&, const FileLire&);
		friend std::istream& operator >> (std::istream&, FileLire&);
	};

	/**
	This structrue describes Schedule items states in the configuration file
	*/
	struct FileScheduleItem {
		unsigned int time; ///< Time the enemy will spawn
		std::string name; ///< Name of the enemy 
		double maxHp; ///< Maximum possible hit points the enemy will have
		double speed; ///< Current speed the enemy will have at the spawn moment
		int money; ///< Money Castle will get for killing the Enemy
		FileScheduleItem() : time(0), name("Enemy"), maxHp(1), speed(0), money(0) {}
		FileScheduleItem(unsigned int _time, std::string _name, double _maxHp, double _speed, int _money);

		friend std::ostream& operator << (std::ostream&, const FileScheduleItem&);
		friend std::istream& operator >> (std::istream&, FileScheduleItem&);
	};

	/**
	This structrue describes Trap states in the configuration file
	*/
	struct FileTrap {
		int x; ///< X cord of the Cell Trap stands on
		int y; ///< Y cord of the Cell Trap stands on
		int effectId; ///< Index of the Effect Trap applies to enemies in the corresponding configuration file
		FileTrap() : x(0), y(0), effectId(0) {}
		FileTrap(int _x, int _y, int _effectId);

		friend std::ostream& operator << (std::ostream&, const FileTrap&);
		friend std::istream& operator >> (std::istream&, FileTrap&);
	};

	/**
	This structrue describes Castle state in the configuration file
	*/
	struct FileCastle {
		int x; ///< X cord of the Cell Castle stands on
		int y; ///< Y cord of the Cell Castle stands on
		int money; ///< Maney balance of the Castle
		std::string title; ///< Title of the Castle
		double maxHp; ///< Maximum hit points the Castle can have
		double curHp; ///< Current hit points the Castle has
		FileCastle() : x(0), y(0), money(0), title("Castle"), maxHp(1), curHp(1) {}
		FileCastle(int _x, int _y, int _money, std::string _title, double _maxHp, double _curHp);

		friend std::ostream& operator << (std::ostream&, const FileCastle&);
		friend std::istream& operator >> (std::istream&, FileCastle&);
	};

	/**
	This structrue describes Effect states in the configuration file
	*/
	struct FileEffect {
		int type; ///< Type of the Effect according to the effectTypeEneum
		int value; ///< Effect magnitude
		unsigned int time; ///< Remaining time of the Effect
		FileEffect() : type(poison), value(0), time(0) {}
		FileEffect(int _type, int _value, unsigned int _time);

		friend std::ostream& operator << (std::ostream&, const FileEffect&);
		friend std::istream& operator >> (std::istream&, FileEffect&);
	};

	/**
	This structrue describes Enemy states in the configuration file
	*/
	struct FileEnemy {
		std::string name; ///< Title of the Enemy
		double cord_x; ///< Current X coordinate of the Enemy
		double cord_y; ///< Current Y coordinate of the Enemy
		double maxHp; ///< Maximum hit points the Enemy can have
		double curHp; ///< Current hit points the Enemy has
		double speed; ///< Raw speed of the Enemy
		int money; ///< Money the Castle will get for killing the Enemy
		int nEffects; ///< Number of Effects applied to the Enemy
		FileEnemy() : name("Enemy"), cord_x(0), cord_y(0), maxHp(1), curHp(1), speed(1), money(0),
			nEffects(0) {}
		FileEnemy(std::string _name, double _cordX, double _cordY, double _maxHp, double _curHp,
			double _speed, int _money, int _nEffects);

		friend std::ostream& operator << (std::ostream&, const FileEnemy&);
		friend std::istream& operator >> (std::istream&, FileEnemy&);
	};

	/**
	This structrue describes Feature states in the configuration file
	*/
	struct FileFeature {
		int level; ///< Level of the Feature
		int price; ///< Price of the Feature
		double damage; ///< Damage of the Tower's shot
		double radius; ///< Raduis of the Tower's attack
		double shotSpeed; ///< Minimum possible time interval between two Tower shots
		FileFeature() : level(1), price(1), damage(1), radius(1), shotSpeed(1) {}
		FileFeature(int _level, int _price, double _damage, double _radius, double _shotSpeed);

		friend std::ostream& operator << (std::ostream&, const FileFeature&);
		friend std::istream& operator >> (std::istream&, FileFeature&);
	};
}

#endif

