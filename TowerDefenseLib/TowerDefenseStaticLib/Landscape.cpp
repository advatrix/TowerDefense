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


}