#pragma once
#include "GraphicsEntity.h"
#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"

using namespace TD;

class GraphicsEnemy: public GraphicsEntity
{
private:
	Enemy* spectatingEnemy;
public:
	void update();
	GraphicsEnemy() : GraphicsEntity(), spectatingEnemy(nullptr) {}

	GraphicsEnemy(char _repr, int txt, int bg, int _x, int _y, Enemy* e) {
		repr = _repr;
		txtColor = txt;
		bgColor = bg;
		x = _x;
		y = _y;
		spectatingEnemy = e;
	}
};

