#pragma once
#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"

#include "GraphicsCell.h"
#include "GraphicsEnemy.h"

using namespace TD;

class GraphicsManager
{
private:
	std::vector<std::vector<GraphicsEntity*>> map;
	std::vector<GraphicsCell*> cells;
	std::vector<GraphicsEnemy*> enemies;
	unsigned n;
public:
	void update(ct::Table<Enemy*>* enemyTable);

	void render();

	friend std::ostream& operator<<(std::ostream& o, const GraphicsManager& g);

	GraphicsManager() : map(), cells(), enemies(), n(0) {}
	GraphicsManager(std::vector<std::vector<Cell*>> _cells, ct::Table<Enemy*>* enemies) {
		int i = 0, j = 0;
		for (auto it = _cells.begin(); it != _cells.end(); it++) {
			
			j = 0;
			for (auto jt = (*it).begin(); jt != (*it).end(); jt++) {
				
				cells.push_back(new GraphicsCell('.', Black, Black, i, j, (*jt), nullptr));
				++j;
			}
			i++;
		}
		map.resize(_cells.size());
		for (auto it = map.begin(); it != map.end(); it++) {
			(*it).resize(_cells[0].size());
		}
	}

	~GraphicsManager() {}

};

