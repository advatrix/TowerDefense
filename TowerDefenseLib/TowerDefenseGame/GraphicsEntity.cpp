#include "GraphicsEntity.h"

std::ostream& operator << (std::ostream& o, const GraphicsEntity& e) {
	setColor(e.txtColor, e.bgColor);
	o << e.repr;
	setColor(White, Black);
	return o;
}

