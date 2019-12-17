#define _CRT_SECURE_NO_WARNINGS

#include "GraphicsEntity.h"

std::ostream& operator << (std::ostream& o, const GraphicsEntity& e) {
	setColor(e.txtColor, e.bgColor);
	setFontSize(25);
	o << e.repr;
	setColor(White, Black);
	return o;
}

void setColor(int txt, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
}

void setFontSize(int size) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInfo;

	fontInfo.cbSize = sizeof(fontInfo);

	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);


	wcscpy(fontInfo.FaceName, L"Lucida Console");

	fontInfo.dwFontSize.Y = size;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
}