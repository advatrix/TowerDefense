#include "pch.h"



#include <iostream>
#include <fstream>
#include <limits>
#include <queue>


#include "Landscape.h"

using namespace nlohmann;

namespace TD {
	/*
	Landscape::Landscape() {
		playingField = nullptr;
		width = 0;
		height = 0;
		nLires = 0;
		enemyTable = EnemyTable();
		castle = nullptr;
	}

	Landscape::Landscape(int level) {
		if (level < 1) throw std::invalid_argument("invalid level number");
		// open file <level>.json here
		// load
		json jLevel;
		std::string filename = std::to_string(level) + ".json";
		std::ifstream f(filename);
		f.open(filename);
		if (!f) throw std::runtime_error("file opening failure");
		else f >> jLevel;
		std::cout << jLevel;
		height = jLevel["height"];
		//...
		width = jLevel["width"];

		NearToTower* neartotower_ = new NearToTower;
		NearToCastle* neartocastle_ = new NearToCastle;
		Strong* strong_ = new Strong;
		Weak* weak_ = new Weak;
		Fast* fast_ = new Fast;
		strategies.push_back(neartotower_);
		strategies.push_back(neartocastle_);
		strategies.push_back(strong_);
		strategies.push_back(weak_);
		strategies.push_back(fast_);

		playingField = new Cell * [height];
		for (int i = 0; i < height; i++) playingField[i] = new Cell[width];
		for (int i = 0; i < height; i++) {
			std::string strI = std::to_string(i);
			for (int j = 0; j < width; j++) {
				std::string strJ = std::to_string(j);
				std::string currCellType = jLevel[strI][strJ].value("type", "forest");
				if (currCellType == "forest")
					playingField[i][j] = new Cell(i, j);
				else if (currCellType == "field") {
					delete playingField[i][j];
					playingField[i][j] = new Field(i, j);
					std::string currBuilding = jLevel[strI][strJ].value("building", "none");
					if (currBuilding == "tower") {
						json tmp = jLevel[strI][strJ]["tower"];
						int strategyType = tmp.value("strategy", 0);
						int featureType = tmp.value("feature", 0);
						unsigned int towerLevel = tmp["tower"].value("level", 1);
						unsigned int lastShot = jLevel[strI][strJ]["tower"].value("lastShot", 0);
						int featurePrice = jLevel[strI][strJ]["tower"].value("price", 100);
						double radius = jLevel[strI][strJ]["tower"].value("radius", 0);
						double damage = jLevel[strI][strJ]["tower"].value("damage", 0);
						double shotSpeed = jLevel[strI][strJ]["tower"].value("shotSpeed", 0);

						Feature* tmpFeature = new Feature(featurePrice, radius, damage, shotSpeed);
						DefaultTower* tmpTower = new DefaultTower(tmpFeature, strategies[strategyType]);
						Building* tmpBuilding = dynamic_cast<Building*>(tmpTower);

						playingField[i][j]->build(tmpBuilding);
					}
					else if (currBuilding == "castle") {
						json tmp = jLevel[strI][strJ]["castle"];

					}
				}
			}
		}
	}
	*/


	void Landscape::loadLevel(int level) {
		/*
		загрузка карты из файла, соответствующего уровню
		для определения имени файла должно использоваться соответствие уровень - имя файла,
		которое также в свою очередь загружается из файла с константным именем
		там же определено, сколько уровней есть всего, чтобы кидать исключение в плохом случае
		так же есть файлы конфигурации фич башен, аналогично для каждого уровня


		можно сделать через json
		*/



	}

	Landscape::Landscape() {
		width = 0;
		height = 0;
		nLires = 0;
		castle = nullptr;
		strategies_[0] = new NearToTower;
		strategies_[1] = new NearToCastle;
		strategies_[2] = new Strong;
		strategies_[3] = new Weak;
		strategies_[4] = new Fast;

		features_[0] = new Feature(1, 0, 1, 1, 10);
		features_[1] = new Feature(2, 10, 3, 2, 8);
	}

	void Landscape::createPath() {
		std::queue<Road*> searchFrontier;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (playingField[i][j]->getType == cellTypeEnum::road) {
					Road* a = dynamic_cast<Road*>(playingField[i][j]);
					if (i > 0 && (playingField[i - 1][j]->type == cellTypeEnum::road)) {
						Road* b = dynamic_cast<Road*>(playingField[i - 1][j]);
						Road::makeNorthSouthNeighbours(b, a);
					}
					if (j > 0 && (playingField[i][j - 1]->type == cellTypeEnum::road)) {
						Road* b = dynamic_cast<Road*>(playingField[i][j - 1]);
						Road::makeWestEastNeighbours(b, a);
					}
					a->clearPath();
				}
		Road* dest = dynamic_cast<Road*>(castle->cell_);
		dest->becomeDestination();
		searchFrontier.push(dest);

		while (!searchFrontier.empty()) {
			Road* tmp = searchFrontier.front();
			searchFrontier.pop();
			if (tmp) {
				searchFrontier.push(tmp->growPathNorth);
				searchFrontier.push(tmp->growPathSouth);
				searchFrontier.push(tmp->growPathEast);				
				searchFrontier.push(tmp->growPathWest);
			}
		}

	}

	bool Landscape::checkWay() const {
		
		
		for (auto i = lires.begin(); i != lires.end(); i++) {
			Road* tmp = dynamic_cast<Road*>((*i)->cell_);
			if (tmp->dist == std::numeric_limits<int>::max()) return false;
		}
		return true;
		
		/*
		for (int i = 0; i < lires.size(); i++) {
			Road* tmp = dynamic_cast<Road*>(lires[i]->cell_);
			if (tmp->dist == std::numeric_limits<int>::max()) return false;
		}
		return true;
		*/
	}

	void Landscape::finish() {
		for (auto i = playingField.begin(); i != playingField.end(); i++) 
			for (auto j = (*i).begin(); j != (*i).end(); j++) delete (*j);
		
		for (auto i = strategies_.begin(); i != strategies_.end(); i++) delete (*i);
		
		// for enemy in emenyTable delete enemy

		

	}

	void Landscape::setCellType(int i, int j, cellTypeEnum type) {
		playingField[i][j]->setType(type);
	}

	bool Landscape::check() const {
		return (checkCastle() && checkLire() && checkWay());
	}

	void Landscape::updateBalance(int mn) {
		castle->updBalance(mn);
	}

	cellTypeEnum Landscape::getCellType(int i, int j) const {
		return playingField[i][j]->type;
	}

	void Road::makeWestEastNeighbours(Road* west, Road* east) {
		if (west->east || east->west) throw std::runtime_error("Redefining neighbours");
		west->east = east;
		east->west = west;
	}

	void Road::makeNorthSouthNeighbours(Road* north, Road* south) {
		if (south->north || north->south) throw std::exception("Redefining neighbours!");
		north->south = south;
		south->north = north;
	}

	void Road::clearPath() {
		next = nullptr;
		dist = std::numeric_limits<int>::max();
	}

	void Road::build(Building* bld) {
		if (building) throw std::runtime_error("Rebuilding");
		building = bld;
		Castle* possibleCastlePtr = nullptr;
		try {
			possibleCastlePtr = dynamic_cast<Castle*>(bld);
		}
		catch (...) {
			return;
		}
		if (possibleCastlePtr) becomeDestination();
	}

	void Road::becomeDestination() {
		dist = 0;
		next = nullptr;
	}

	void Road::growPathTo(Road* neighbour) {
		if (!hasPath()) throw std::runtime_error("No path");
		if (!neighbour || neighbour->hasPath()) return;
		neighbour->dist = dist + 1;
		neighbour->next = this;
	}

	Road* Road::growPathToNeighbour(Road* neighbour) {
		if (!hasPath()) throw std::runtime_error("No path");
		if (!neighbour || neighbour->hasPath()) return nullptr;
		neighbour->dist = dist + 1;
		neighbour->next = this;
		return neighbour;
	}

	void Field::destroy() {
		if (tower) delete tower;
	}

	Cell* Cell::setType(cellTypeEnum newType) {
		destroy();
		switch (newType) {
		case forest: {
			Cell* tmp = new Cell(x, y);
			delete this;
			return tmp;
		}
		case field: {
			Cell* tmp = new Field(x, y);
			delete this;
			return tmp;
		}
		case road: {
			Cell* tmp = new Road(x, y);
			delete this;
			return tmp;
		}
		default:
			throw std::invalid_argument("wrong cell type");
		}
	}

	Cell::Cell() {
		x = 0;
		y = 0;
		type = forest;
	}

	Cell::Cell(int x_, int y_) {
		x = x_;
		y = y_;
		type = forest;
	}

	void Road::destroy() {
		Trap* possibleTrap;
		try {
			possibleTrap = dynamic_cast<Trap*>(building);
		}
		catch (...) {
			throw std::exception("impossible to destroy");
		}
		if (possibleTrap) delete building;
		else throw std::exception("impossible to destroy");
	}

	Road::Road(int i, int j) {
		building = nullptr;
		west = nullptr;
		east = nullptr;
		north = nullptr;
		south = nullptr;
		next = nullptr;
		dist = std::numeric_limits<int>::max();
		x = i;
		y = j;
	}

	Road::Road() {
		building = nullptr;
		west = nullptr;
		east = nullptr;
		north = nullptr;
		south = nullptr;
		next = nullptr;
		dist = std::numeric_limits<int>::max();
		x = 0;
		y = 0;
	}

	Road::~Road() {
		try {
			destroy();
		}
		catch (...) {
			;
		}
	}

	void Field::build(Tower* tw) {
		if (tw) tower = tw;
		else throw std::invalid_argument("tower nullptr");
	}

	Field::Field() {
		x = 0;
		y = 0;
		tower = nullptr;
	}
	
	Field::Field(int i, int j) {
		x = i;
		y = j;
		tower = nullptr;
	}

	Field::~Field() {
		delete tower;
	}

	Cords::Cords() {
		x = 0;
		y = 0;
	}

	Cords::Cords(double _x, double _y) {
		x = _x;
		y = _y;
	}

	/*
	EnemyTable::Iterator EnemyTable::begin()
	{
		return EnemyTableIt(arr.begin());
	}

	EnemyTable::Iterator EnemyTable::end()
	{
		return EnemyTableIt(arr.end());
	}

	int EnemyTableIt::operator !=(const EnemyTableIt& it) const
	{
		return cur != it.cur;
	}
	int EnemyTableIt::operator ==(const EnemyTableIt& it) const
	{
		return cur == it.cur;
	}

	std::vector<Enemy*> & EnemyTableIt::operator *()
	{
		return *cur;
	}

	std::pair<const std::string, int>* ConstAssocIt::operator ->()
	{
		return &(*cur);
	}

	ConstAssocIt& ConstAssocIt::operator ++()
	{
		++cur;
		return *this;
	}

	ConstAssocIt ConstAssocIt::operator ++(int)
	{
		ConstAssocIt res(*this);
		++cur;
		return res;
	}
	*/

	void EnemyTable::add(Enemy* e) {
		if (e) arr.push_back(e);
		else throw std::invalid_argument("enemy nullptr");
	}

	void EnemyTable::update() {
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i]->hp()) arr[i]->turn();
			else {
				delete arr[i];
				arr.erase(arr.begin() + i);
			}
		}		
	}

	void EnemyTable::erase() {
		for (int i = 0; i < arr.size(); i++) delete arr[i];
	}

	std::pair<double, double> Cell::cords() const {
		return std::pair<double, double>(x, y);
	}

	Enemy* EnemyTable::operator[] (int i) const {
		return arr[i];
	}


	Landscape::~Landscape() {
		for (int i = 0; i < playingField.size(); i++)
			for (int j = 0; j < playingField[i].size(); j++)
				delete playingField[i][j];

		delete enemyTable;
	}

	bool Landscape::makeTurn() {
		for (int i = 0; i < enemyTable->size(); i++)
			(*enemyTable)[i]->turn();
		for (int i = 0; i < lires.size(); i++)
			lires[i]->spawnByTime();
		if (!castle->getHp()) return false;
		for (int i = 0; i < playingField.size(); i++)
			for (int j = 0; j < playingField[i].size(); j++) {
				Field* prField = dynamic_cast<Field*>(playingField[i][j]);
				if (prField) {
					bool b = prField->isBuilt();
					if (b) prField->getTower()->attack();
				}
				else {
					Road* prRoad = dynamic_cast<Road*>(playingField[i][j]);
					if (prRoad) {
						bool b = prRoad->isBuilt();
						if (b) {
							Trap* prTrap = dynamic_cast<Trap*>(prRoad->getBuilding());
							if (prTrap) prTrap->attack();
						}
					}
				}

			}


	}






}
