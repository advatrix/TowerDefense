#include "GraphicsManager.h"

void GraphicsManager::update(ct::Table<Enemy*>* enemyTable) {
	for (auto it = enemies.begin(); it != enemies.end(); it++)
		delete (*it);
	enemies.clear();
	for (auto it = enemyTable->begin(); it != enemyTable->end(); it++)
		enemies.push_back(new GraphicsEnemy(7, Red, Black, floor((*it)->getCords().first),
			floor((*it)->getCords().second), (*it)));
}

void GraphicsManager::render() {
	   
	for (auto it = cells.begin(); it != cells.end(); it++) {
		(*it)->update();
		map[(*it)->getX()][(*it)->getY()] = (*it);
	}

	for (auto it = enemies.begin(); it != enemies.end(); it++)
		map[(*it)->getX()][(*it)->getY()] = (*it);

	
}

std::ostream& operator<<(std::ostream& o, const GraphicsManager& g) {
	for (auto it = g.map.begin(); it != g.map.end(); it++) {
		for (auto jt = (*it).begin(); jt != (*it).end(); jt++)
			std::cout << *(*jt);
		std::cout << std::endl;
	}
	return o;
}
