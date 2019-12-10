#pragma once
#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"
#include "GraphicsEntity.h"

using namespace TD;

class GraphicsCell : public GraphicsEntity 
{
private:
	Cell* spectationCell;
	Building* spectationBuilding;
	void setBuilding(Building* b) { spectationBuilding = b; }
public:
	GraphicsCell() : GraphicsEntity(), spectationCell(nullptr), spectationBuilding(nullptr) {}
	
	GraphicsCell(char repr, int txt, int bg, int x, int y, Cell* c, Building* b) :
		GraphicsEntity(repr, txt, bg, x, y), spectationCell(c), spectationBuilding(b) {}

	void update();

};

