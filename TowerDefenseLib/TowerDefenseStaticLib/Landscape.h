#pragma once

#include <string>
#include <vector>
#include <array>

#include "json.hpp"


#include "Enemy.h"
#include "Building.h"
#include "Tower.h"

using namespace nlohmann;

namespace TD {
	class Landscape {
	private:
		std::vector<std::vector<Cell*>> playingField;
		std::vector<Strategy*> strategies;
		unsigned int width;
		unsigned int height;
		unsigned int nLires;
		EnemyTable enemyTable;
		Castle* castle;
		std::vector<Lire*> lires;
		inline bool checkCastle() const { return castle; }
		bool checkLire();
		bool checkWay();
		void makeTurn();
		void createPath();
		void download();
		void loadLevel(int);
	public:
		Landscape();
		Landscape(int length, int, int nLires); // возможно надо будет убрать в будущем
		Landscape(int);
		inline unsigned int getSize() const {
			return width * height;
		}
		void setSize(int height, int wigth);
		CellType getCellType(int n, int m) const;
		void setCellType(int n, int m, CellType type);
		bool check() const;
		inline unsigned int getWidth() const {
			return width;
		}
		inline unsigned int getHeight() const {
			return height;
		}
		void start();
		~Landscape();
		void constructLevel() const;

	};

	enum CellType { forest, road, field };
	enum StrategyType { nearToTower, nearToCastle, strong, weak, fast };

	class Cell {
	protected:
		int x;
		int y;
		Cords* cords;
	public:
		Cell& setType(CellType);
		Cell();
		Cell(int, int);
		virtual void build(Building*) {}
		virtual void getDist() {}
		virtual void updPath() {}
	};


	class Road : public Cell {
	private:
		Trap* trap;
		Road* west;
		Road* east;
		Road* north;
		Road* south;
		Road* next;
		int dist;
	public:
		void build(Trap *);
		void updPath(Cell*, int);
		Road();
		~Road();
		Road(int, int);
		int getDist() const;
	};

	class Field : public Cell {
	private:
		Building* building;
	public:
		void build(Building *);
		Field();
		Field(int i, int j);
		~Field();
	};

	class Cords {
	private:
		double x;
		double y;
	public:
		Cords();
		double getX() const;
		double getY() const;
	};

	class EnemyTable {
	private:
		std::pair<Cords*, Enemy*>* enemyTableItem;
	public:
		EnemyTable();
		void update();
		friend class EnemyTableIterator;
	};

	class EnemyTableIterator {
	private:
		std::pair<Cords*, Enemy*>* cur;
	public:
		EnemyTableIterator next();
		EnemyTableIterator();
	};




}
