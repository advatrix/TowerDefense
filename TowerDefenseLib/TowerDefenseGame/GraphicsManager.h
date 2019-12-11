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

	~GraphicsManager() {}

};

