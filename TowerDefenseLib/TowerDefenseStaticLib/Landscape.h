#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <vector>

#include "Table.h"

#include "Cell.h"
#include "Enemy.h"

namespace ct = customTemplates;

namespace TD {
	class Landscape {
	private:
		std::vector<std::vector<Cell*>> cells;
		unsigned int height;
		unsigned int width;

		ct::Table<Enemy*>* enemyTable;
		
	public:
		Landscape() : cells(), height(0), width(0) {}
		Landscape(std::vector<std::vector<Cell*>>& _cells);

		inline unsigned int getHeight() const { return height; }
		inline unsigned int getWidth() const { return width; }
	
		Cell* getCell(int i, int j) const;
		ct::Table<Enemy*>* getEnemyTable() const { return enemyTable; }

		bool createPath();
	};

}

#endif
