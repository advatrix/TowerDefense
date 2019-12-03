#pragma once

#include <string>
#include <vector>
#include <array>
#include <map>

#include "FileStructs.h"
#include "Cell.h"




// #include "Enemy.h"
// #include "Building.h"
// #include "Tower.h"


namespace TD {
	class Enemy;
	class EnemyTable;
	class Castle;
	class Lire;
	class Strategy;
	class Feature;
	class Building;
	class Tower;
	class Effect;
	class EnemySchedule;


	




	class Landscape {
	private:
		std::vector<std::vector<Cell*>> playingField;
		unsigned int width;
		unsigned int height;
		unsigned int nLires;

		EnemyTable* enemyTable;
		Castle* castle;
		std::vector<Lire*> lires;

		std::array<Strategy*, 5> strategies_;
		std::array<Feature*, 2> features_;

		unsigned int time;

		inline bool checkCastle() const { return castle; }
		inline bool checkLire() const { return nLires > 0; }
		bool checkWay() const;
		bool makeTurn();
		void createPath();
		void loadLevel(int);
		void finish();

		void updateBalance(int money);
	public:
		Landscape();
		// Landscape(int length, int, int nLires); // возможно надо будет убрать в будущем
		Landscape(int level);
		inline unsigned int getSize() const {
			return width * height;
		}
		void setSize(int height, int width) = delete; // как оно должно работать?
		cellTypeEnum getCellType(int n, int m) const;
		void setCellType(int n, int m, cellTypeEnum type) throw (std::invalid_argument);
		bool check() const;
		inline unsigned int getWidth() const {return width; } 
		inline unsigned int getHeight() const {	return height;}
		inline unsigned int getTime() const { return time; }
		void start(int); // TODO
		~Landscape();
		// void constructLevel() const = delete; // ???

		inline std::array<Strategy*, 5> strategies() const { return strategies_; }
		inline std::array<Feature*, 2> features() const { return features_; }

		inline EnemyTable* table() const { return enemyTable; }
		inline Castle* getCastle() const { return this->castle; }

		inline Cell* getCell(int i, int j) const { return playingField[i][j]; }


		friend class DefaultTower;

		friend class NearToCastle;
		friend class NearToTower;
		friend class Strong;
		friend class Weak;
		friend class Fast;

		friend class Lire;
	};

	


	class Road : public Cell {
	private:
		Building* building; 
		Road* west;
		Road* east;
		Road* north;
		Road* south;
		Road* next;
		int dist;
		static void makeWestEastNeighbours(Road* west, Road* east);
		static void makeNorthSouthNeighbours(Road* north, Road* south);
		void clearPath();
		void becomeDestination();
		void growPathTo(Road* neighbour);
		Road* growPathToNeighbour(Road* neighbour);
		inline Road* growPathNorth() { return growPathToNeighbour(north); }
		inline Road* growPathSouth() { return growPathToNeighbour(south); }
		inline Road* growPathWest() { return growPathToNeighbour(west); }
		inline Road* growPathEast() { return growPathToNeighbour(east); }
	public:
		void build(Building *);
		void destroy() throw (std::exception);
		inline bool isBuilt() { return building; }
		~Road();
		Road();
		Road(int, int);
		inline int getDist() const { return dist; }
		inline bool hasPath() const { return dist != std::numeric_limits<int>::max(); }
		inline Building* getBuilding() const { return building; }
		friend class Landscape;
		friend class Road;

		inline Road* getNext() const { return next; }



	};

	class Field : public Cell {
	private:
		Tower* tower;
	public:
		void build(Tower *) throw (std::invalid_argument);
		Field();
		Field(int i, int j);
		~Field();
		void destroy();
		inline bool isBuilt() { return tower; }
		inline Tower* getTower() const { return tower; }
	};

	class Cords {
	private:
		double x;
		double y;
	public:
		Cords();
		Cords(double, double);
		inline double getX() const { return x; }
		double getY() const { return y; }
	};
	/*
	class EnemyTable {
	private:
		std::vector<Enemy*> arr;
	public:
		EnemyTable() {}
		void update();
		friend class EnemyTableIt;
		typedef EnemyTableIt Iterator;
		Iterator begin();
		Iterator end();

	};

	class EnemyTableIt {
	private:
		std::vector<Enemy*>::iterator cur;
	public:
		EnemyTableIt() {}
		EnemyTableIt(std::vector<Enemy*>::iterator it): cur(it) {}
		EnemyTableIt next();
		EnemyTableIt();

		int operator !=(const EnemyTableIt&) const;
		int operator ==(const EnemyTableIt&) const;
		
		std::vector<Enemy*>& operator *();
		std::vector<Enemy*>* operator ->();

		EnemyTableIt& operator ++();
		EnemyTableIt operator ++(int);

	};

	*/

	class EnemyTable {
	private: 
		std::vector<Enemy*> arr;
	public:
		EnemyTable() {}
		void add(Enemy*);
		void update();
		void erase();
		~EnemyTable() { erase(); }
		inline int size() { return arr.size(); }
		// int find(Enemy*) const;

		Enemy* operator[] (int) const;
	};

	class Building {
	protected:
		Cell* cell_;
	public:
		Building();
		Building(Cell*);
		virtual ~Building() {}
		std::pair<double, double> cords() const;
	};

	class Tower : public Building {
	protected:
		unsigned int level_;
		unsigned int lastShot_;
		Feature* feature_;
		strategyTypeEnum strategyType_;

		Landscape* land;
	public:
		virtual void upgrade() = 0;
		virtual void attack() = 0;
		inline void tick() { ++lastShot_; }
		inline Landscape* ls() const { return land; }
		virtual void fire(Enemy*) = 0;
		virtual strategyTypeEnum strategyType() const = 0;
		inline unsigned int getLevel() const { return level_; }
	};

	class Feature {
	private:
		int price_;
		double radius_;
		double damage_;
		unsigned int shotSpeed_;
		int level_;
	public:
		// void behaviour();
		Feature() : price_(0), radius_(0), damage_(0), shotSpeed_(0), level_(0) {}
		friend class Tower;
		inline int price() const { return price_; }
		inline double radius() const { return radius_; }
		inline double damage() const { return damage_; }
		inline double shotSpeed() const { return shotSpeed_; }
		inline int level() const { return level_; }
		Feature(int level, int price, double raduis, double damage, double shotSpeed);
	};

	class DefaultTower : public Tower {
	protected:
		Strategy* strategy_;
		strategyTypeEnum strategyType_;
	public:
		DefaultTower();
		DefaultTower(Cell*, Feature*, Strategy*, Landscape*);
		DefaultTower(Landscape*);
		void attack();
		void upgrade();
		void fire(Enemy*);
		friend class Strategy;
		inline strategyTypeEnum strategyType() const { return strategyType_; }
	};

	class Strategy {
	public:
		virtual void attack(Tower*) = 0;
		virtual ~Strategy() {}
		static double distance(Enemy*, Building*);
	};

	

	class MagicEntity {
	protected:
		Effect* effect;
		std::vector<Enemy*> attached;
		Landscape* land_;
	public:
		void applyEffect(Enemy*);
		virtual ~MagicEntity() {}
	};

	class Trap : Building, MagicEntity {
	public:
		void attack();
		Trap();
		Trap(Landscape*);
		Trap(Landscape*, Cell*, effectTypeEnum, int value, unsigned int time);
	};

	class MagicTower : DefaultTower, MagicEntity {
	public:
		MagicTower();
		MagicTower(Landscape*, Cell*, Feature*, Strategy*, effectTypeEnum, int, unsigned int);
	};

	

	class Castle : public Building {
	private:
		double curHp_;
		double maxHp_;
		int money_;
		std::string title_;
	public:
		Castle();
		inline double getHp() const { return curHp_; }
		inline std::string getTitle() const { return title_; }
		inline void damage(double quant) { curHp_ -= quant; }
		inline void updBalance(int income) { money_ += income; }
		Castle(Cell*, double curHp, double maxHp, int money, std::string title);

		friend class Landscape;

	};

	class Lire : public Building {
	private:
		EnemySchedule* schedule;
		Landscape* land;
	public:
		void spawn(Enemy*);
		void spawnByTime();
		Lire();
		Lire(Cell*, EnemySchedule*, Landscape*);
		~Lire() { delete schedule; }
		friend class Landscape;
		inline EnemySchedule* getSchedule() const { return schedule; }
	};

	
	/*
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
		// std::vector<int> effectsId;
		FileEnemy() : name("Enemy"), cord_x(0), cord_y(0), maxHp(1), curHp(1), speed(1), money(0),
			nEffects(0) /*, effectsId()  {}
		FileEnemy(std::string _name, double _cordX, double _cordY, double _maxHp, double _curHp,
			double _speed, int _money, int _nEffects, std::vector<int> _effectsId);

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
	*/
	class Road;
	class Landscape;
	class Effect;


	class EffectTable {
	private:
		std::vector<Effect*> effectsVec;
	public:
		EffectTable() {}
		~EffectTable();
		void addEffect(Effect*);
		// friend class EffectTableIterator;
		Effect* operator[] (int index);
		// Effect* operator[] (int);
		inline int getSize() const { return effectsVec.size(); }
	};



	class Enemy {
	protected:
		std::string title;
		double maxHp;
		double curHp;
		int money;
		double speed;
		double realSpeed;
		double dmgMultiplier = 1;
		EffectTable* effects;
		Road* road;
		// Cords* cords;
		Landscape* land_;
		double x_;
		double y_;
		void move();
		void calculateHp();
	public:
		Enemy();

		Enemy(std::string _title, double _max, double _cur, int _money, double _speed, std::vector<Effect*> _effects, double _x, double _y, Landscape* land);


		void turn();
		void hit(Castle*);
		void getHurt(double);

		void addEffect(Effect*);
		~Enemy() {}
		friend class Effect;
		friend class Weakness;
		friend class Slowdown;
		friend class Poison;



		inline double hp() const { return curHp; }
		std::pair<double, double> cords() const;
		inline double spd() const { return speed; }
		void setCords(std::pair<double, double>);

	};

	enum directionEnum { north, east, south, west };



	class EnemySchedule {
	private:
		std::multimap<unsigned int, Enemy*> schedule; // std multi map
	public:
		EnemySchedule(std::multimap<unsigned int, Enemy*>);
		~EnemySchedule() {}
		// friend class EnemyScheduleIterator;

		std::vector<Enemy*> find(unsigned int);
	};




}
