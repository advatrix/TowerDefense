#pragma once

#include <string>
#include <vector>
#include <array>

#include "json.hpp"


#include "Enemy.h"
#include "Building.h"
#include "Tower.h"

#include "FileStructs.h"

using namespace nlohmann;

namespace TD {
	class Landscape {
	private:
		std::vector<std::vector<Cell*>> playingField;
		// std::vector<Strategy*> strategies;
		unsigned int width;
		unsigned int height;
		unsigned int nLires;

		EnemyTable* enemyTable;
		Castle* castle;
		std::vector<Lire*> lires;

		static std::array<Strategy*, 5> strategies_;
		static std::array<Feature*, 2> features_;

		unsigned int time;

		inline bool checkCastle() const { return castle; }
		inline bool checkLire() const { return nLires > 0; }
		bool checkWay() const;
		bool makeTurn();
		void createPath();
		// void load();
		void loadLevel(int);
		void finish();

		void updateBalance(int money);
	public:
		Landscape();
		// Landscape(int length, int, int nLires); // возможно надо будет убрать в будущем
		Landscape(int);
		inline unsigned int getSize() const {
			return width * height;
		}
		void setSize(int height, int width) = delete; // как оно должно работать?
		cellTypeEnum getCellType(int n, int m) const;
		void setCellType(int n, int m, cellTypeEnum type) throw (std::invalid_argument);
		bool check() const;
		inline unsigned int getWidth() const {return width; } 
		inline unsigned int getHeight() const {	return height;}
		void start();
		~Landscape();
		void constructLevel() const = delete; // ???

		inline std::array<Strategy*, 5>& strategies() const { return strategies_; }
		inline std::array<Feature*, 2> & features() const { return features_; }


		friend class DefaultTower;

		friend class NearToCastle;
		friend class NearToTower;
		friend class Strong;
		friend class Weak;
		friend class Fast;
	};

	class Cell {
	protected:
		int x;
		int y;
		// Cords* cords;
		static cellTypeEnum type;
	public:
		Cell* setType(cellTypeEnum) throw (std::invalid_argument, std::exception);
		inline cellTypeEnum getType() const { return type; }
		Cell();
		Cell(int, int);
		virtual void destroy() {}
		// virtual void build(Building*) {}
		// virtual void getDist() {}
		// virtual void updPath() {}
		virtual ~Cell() {}
		std::pair<double, double> cords() const;
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
		void destroy() throw (std::exception); //???
		inline bool isBuilt() { return building; }
		// void updPath(Cell*, int);
		~Road();
		Road();
		Road(int, int);
		inline int getDist() const { return dist; }
		inline bool hasPath() const { return dist != std::numeric_limits<int>::max(); }
		friend class Landscape;
		friend class Road;
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

		Enemy* operator[] (int) const;
	};



}
