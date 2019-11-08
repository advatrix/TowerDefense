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
		загрузка карты из файла, соответствующего уровню
		для определения имени файла должно использоваться соответствие уровень - имя файла,
		которое также в свою очередь загружается из файла с константным именем
		там же определено, сколько уровней есть всего, чтобы кидать исключение в плохом случае
		так же есть файлы конфигурации фич башен, аналогично для каждого уровня
		
		*/
	}

	void Landscape::constructLevel() const {
		int len, wid, n;
		
		
	}
}
