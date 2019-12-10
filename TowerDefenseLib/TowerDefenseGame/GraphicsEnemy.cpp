#include "GraphicsEnemy.h"

void GraphicsEnemy::update() {
	x = floor(spectatingEnemy->getCords().first);
	y = floor(spectatingEnemy->getCords().second);
}
