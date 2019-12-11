#include "GraphicsEntity.h"

std::ostream& operator << (std::ostream& o, const GraphicsEntity& e) {
	setColor(e.txtColor, e.bgColor);
	o << e.repr;
	setColor(White, Black);
	return o;
}

void setColor(int txt, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
}

