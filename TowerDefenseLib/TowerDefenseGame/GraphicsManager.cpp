#include "GraphicsManager.h"

void GraphicsManager::update(ct::Table<Enemy*>* enemyTable) {
	for (auto it = enemies.begin(); it != enemies.end(); it++)
		delete (*it);
	enemies.clear();
	for (auto it = enemyTable->begin(); it != enemyTable->end(); it++) {
		Colors color = Red;
		if ((*it)->getEffects().getSize())
			switch ((*it)->getEffects()[0]->getType()) {
			case effectTypeEnum::poison:
				color = Green;
				break;
			case effectTypeEnum::slowdown:
				color = LightBlue;
				break;
			case effectTypeEnum::weakness:
				color = Magenta;
				break;
			}


		enemies.push_back(new GraphicsEnemy('.', color, LightGray, floor((*it)->getCords().first),
			floor((*it)->getCords().second), (*it)));
	}
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
	std::cout << std::endl << '#';
	for (int i = 0; i < g.map[0].size(); i++) std::cout << i;
	std::cout << "Y" << std::endl;
	int j = 0;
	for (auto it = g.map.begin(); it != g.map.end(); it++) {
		std::cout << j++;
		for (auto jt = (*it).begin(); jt != (*it).end(); jt++)
			std::cout << *(*jt);
		std::cout << std::endl;
	}
	std::cout << "X" << std::endl << std::endl;
	return o;
}
