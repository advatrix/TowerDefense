#include "pch.h"



#include <iostream>


#include "Landscape.h"

namespace TD {
	Landscape::Landscape() {
		playingField = nullptr;
		length = 0;
		height = 0;
		nLires = 0;
		enemyTable = EnemyTable();
		castle = nullptr;
	}

	Landscape::Landscape(int length, int width, int n) {
		if (length < 1) throw std::exception("incorrect length");
		if (width < 1) throw std::exception("incorrect width");
		if (n < 1) throw std::exception("there should be at least one lire");
		loadLevel(length, width, n, 1);
		
	}

	void Landscape::loadLevel(int length, int width, int n, int level) {
		/*
		�������� ����� �� �����, ���������������� ������
		��� ����������� ����� ����� ������ �������������� ������������ ������� - ��� �����,
		������� ����� � ���� ������� ����������� �� ����� � ����������� ������
		��� �� ����������, ������� ������� ���� �����, ����� ������ ���������� � ������ ������
		��� �� ���� ����� ������������ ��� �����, ���������� ��� ������� ������
		
		*/
	}

	void Landscape::constructLevel() const {
		int len, wid, n;
		
		
	}
}
