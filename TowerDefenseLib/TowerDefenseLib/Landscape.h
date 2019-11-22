#pragma once

#include <string>
#include <vector>
#include <array>

#include "Enemy.h"
#include "Building.h"
#include "Tower.h"

namespace TD {
	class Landscape {
	private:
		Cell** playingField;
		unsigned int length;
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
		int getSize() const;
		void setSize(int length, int wigth);
		CellType getCellType(int n, int m) const;
		void setCellType(int n, int m, CellType type);
		bool check() const;
		unsigned int getLength() const;
		unsigned int getHeight() const;
		void startGame();
		~Landscape();
		void constructLevel() const;

};

	enum CellType{forest, road, field};

	class Cell {
	protected:
		int x;
		int y;
		Cords* cords;
	public:
		Cell& setType(CellType);
		Cell();
		Cell(int, int);
	};

	class Road : Cell {
	private:
		Trap* trap;
		Road* west;
		Road* east;
		Road* north;
		Road* south;
		Road* next;
		int dist;
	public:
		void build(Trap&);
		void updPath(Cell*, int);
		Road();
		~Road();
		int getDist() const;
	};

	class Field : Cell {
	private:
		Building* building;
	public:
		void build(Building&);
		Field();
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
