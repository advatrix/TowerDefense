#include "pch.h"
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
		for (auto it = cells.begin(); it != cells.end(); it++)
			for (auto jt = (*it).begin(); jt != (*it).end(); jt++)
				delete (*jt);

		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++)
			delete (*it);
	}

	void Landscape::update() {
		for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
			moveEnemy(*it);
		}
	}

	void Landscape::moveEnemy(Enemy* e) {
		std::pair<double, double> cords = e->getCords();
		Road* cellEnemyOn = dynamic_cast<Road*>(cells[floor(cords.first)][floor(cords.second)]);
		std::pair<double, double> target = cellEnemyOn->getNext()->cords();
		double deltaX = abs(floor(cords.first) - target.first) * e->getCurSpeed();
		double deltaY = abs(floor(cords.second) - target.second) * e->getCurSpeed();
		e->move(deltaX, deltaY);
		 
	}

}