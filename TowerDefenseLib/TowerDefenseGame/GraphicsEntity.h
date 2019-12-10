#pragma once
#include <iostream>
#include <Windows.h>


enum Colors {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};


void setColor(int txt, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
}

class GraphicsEntity
{
protected:
	char repr;
	int txtColor;
	int bgColor;
	int x;
	int y;
public:
	
	friend std::ostream& operator <<(std::ostream& o, const GraphicsEntity& e);
	virtual void update() = 0;
	inline void setRepr(char sample) { repr = sample; }
	inline void setTxtColor(int newColor) { txtColor = newColor; }
	inline void setBgColor(int newColor) { bgColor = newColor; }

	inline int getX() const { return x; }
	inline int getY() const { return y; }

	GraphicsEntity() {
		repr = 219;
		txtColor = White;
		bgColor = Black;
		x = 0;
		y = 0;
	}

	GraphicsEntity(char _repr, int _txtColor, int _bgColor, int _x, int _y) {
		repr = _repr;
		txtColor = _txtColor;
		bgColor = _bgColor;
		x = _x;
		y = _y;
	}

	~GraphicsEntity() {}
};

