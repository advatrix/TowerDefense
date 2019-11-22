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

	Landscape::Landscape(int level) {
		if (level < 1) throw std::invalid_argument("invalid level number");
		// open file <level>.json here
		// load

	}

	Landscape::Landscape(int length, int height, int n) {
		if (length < 1) throw std::exception("incorrect length");
		if (height < 1) throw std::exception("incorrect width");
		if (n < 1) throw std::exception("there should be at least one lire");
		//loadLevel();
		
	}

	void Landscape::loadLevel(int level) {
		/*
		загрузка карты из файла, соответствующего уровню
		для определения имени файла должно использоваться соответствие уровень - имя файла,
		которое также в свою очередь загружается из файла с константным именем
		там же определено, сколько уровней есть всего, чтобы кидать исключение в плохом случае
		так же есть файлы конфигурации фич башен, аналогично для каждого уровня
		

		можно сделать через json
		*/
	}

	void Landscape::constructLevel() const {
		int len, wid, n;
		
		
	}
}
