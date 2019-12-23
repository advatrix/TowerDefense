#include "pch.h"
#include <queue>
#include "Landscape.h"


namespace TD {
	Cell* Landscape::getCell(int i, int j) const {
		if (i < 0 || j < 0) throw std::out_of_range("negative cords");
		if (i > height || j > width) throw std::out_of_range("cords out of range");
		return cells[i][j];
	}

	Landscape::Landscape(std::vector<std::vector<Cell*>>& _cells) {
		cells = _cells;
		height = _cells.size();
		width = _cells[0].size();

	}

	Landscape::~Landscape() {
		/*
		for (auto it = cells.begin(); it != cells.end(); it++)
			for (auto jt = (*it).begin(); jt != (*it).end(); jt++)
				if (*jt) delete (*jt);

		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++)
			if (*it) delete (*it);
			*/
	}

	void Landscape::update() {
		if (enemyTable) {
			for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
				if ((*it)->getCurHp()) moveEnemy(*it);
				else {
					castle_->incMoney((*it)->getMoney());
					enemyTable->remove(*it);
				}
			}
		}
	}

	void Landscape::moveEnemy(Enemy* e) {
		std::pair<double, double> cords = e->getCords();
		Road* cellEnemyOn = dynamic_cast<Road*>(cells[floor(cords.first)][floor(cords.second)]);
		if (cellEnemyOn->dist == 0) {
			castle_->decHp(e->getCurHp());
			enemyTable->remove(e);
			return;
		}
		std::pair<double, double> target = cellEnemyOn->getNext()->cords();
		double deltaX = target.first - floor(cords.first);
		double deltaY = target.second - floor(cords.second);
		if (e->getCurSpeed() > 1) {
			std::vector<Cell*> missingCells;
			std::pair<double, double> targetCell;
			// просчитать клетки, который враг потенциально может проскочить
			// и дернуть ловушки, находящиеся на них
		}
		e->move(deltaX, deltaY);
		cords = e->getCords();
		std::pair<double, double> cc = castle_->getCords();
		if (floor(cords.first) == floor(cc.first) && floor(cords.second) == floor(cc.second))
			castle_->decHp(e->getCurHp());
		 
	}

	bool Landscape::createPath() {
		std::pair<double, double> dest = castle_->getCords();
		Road* r = dynamic_cast<Road*>(cells[dest.first][dest.second]);
		
		std::vector<Road*> liresCells;
		std::queue<Road*> searchFrontier;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (cells[i][j]->getType() == cellTypeEnum::road) {
					Road* a = dynamic_cast<Road*>(cells[i][j]);
					if (i > 0 && (cells[i - 1][j]->getType()) == cellTypeEnum::road) {
						Road* b = dynamic_cast<Road*>(cells[i - 1][j]);
						Road::makeNorthSouthNeighbours(b, a);
					}
					if (j > 0 && cells[i][j - 1]->getType() == cellTypeEnum::road) {
						Road* b = dynamic_cast<Road*>(cells[i][j - 1]);
						Road::makeWestEastNeighbours(b, a);
					}
					if (a->getBuilding() && a->getBuilding()->getType() == buildingTypeEnum::lire)
						liresCells.push_back(a);
					a->clearPath();
				}

		if (liresCells.empty()) return false;

		r->becomeDestination();
		searchFrontier.push(r);

		while (!searchFrontier.empty()) {
			Road* tmp = searchFrontier.front();
			searchFrontier.pop();
			if (tmp) {
				searchFrontier.push(tmp->growPathNorth());
				searchFrontier.push(tmp->growPathSouth());
				searchFrontier.push(tmp->growPathEast());
				searchFrontier.push(tmp->growPathWest());
			}
		}

		for (auto it = liresCells.begin(); it != liresCells.end(); it++) {
			if ((*it)->getDist() == std::numeric_limits<unsigned>::max()) return false;
		}
		return true;
		
	}

	Landscape::Landscape(std::vector<std::vector<Cell*>>& _cells, ct::Table<Enemy*>* et) {
		cells = _cells;
		enemyTable = et;
		castle_ = nullptr;
		height = cells.size();
		width = cells[0].size();
	}

}