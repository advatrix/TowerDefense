#include "pch.h"



#include <iostream>
#include <fstream>


#include "Landscape.h"

using namespace nlohmann;

namespace TD {
	/*
	Landscape::Landscape() {
		playingField = nullptr;
		width = 0;
		height = 0;
		nLires = 0;
		enemyTable = EnemyTable();
		castle = nullptr;
	}

	Landscape::Landscape(int level) {
		if (level < 1) throw std::invalid_argument("invalid level number");
		// open file <level>.json here
		// load
		json jLevel;
		std::string filename = std::to_string(level) + ".json";
		std::ifstream f(filename);
		f.open(filename);
		if (!f) throw std::runtime_error("file opening failure");
		else f >> jLevel;
		std::cout << jLevel;
		height = jLevel["height"];
		//...
		width = jLevel["width"];

		NearToTower* neartotower_ = new NearToTower;
		NearToCastle* neartocastle_ = new NearToCastle;
		Strong* strong_ = new Strong;
		Weak* weak_ = new Weak;
		Fast* fast_ = new Fast;
		strategies.push_back(neartotower_);
		strategies.push_back(neartocastle_);
		strategies.push_back(strong_);
		strategies.push_back(weak_);
		strategies.push_back(fast_);

		playingField = new Cell * [height];
		for (int i = 0; i < height; i++) playingField[i] = new Cell[width];
		for (int i = 0; i < height; i++) {
			std::string strI = std::to_string(i);
			for (int j = 0; j < width; j++) {
				std::string strJ = std::to_string(j);
				std::string currCellType = jLevel[strI][strJ].value("type", "forest");
				if (currCellType == "forest")
					playingField[i][j] = new Cell(i, j);
				else if (currCellType == "field") {
					delete playingField[i][j];
					playingField[i][j] = new Field(i, j);
					std::string currBuilding = jLevel[strI][strJ].value("building", "none");
					if (currBuilding == "tower") {
						json tmp = jLevel[strI][strJ]["tower"];
						int strategyType = tmp.value("strategy", 0);
						int featureType = tmp.value("feature", 0);
						unsigned int towerLevel = tmp["tower"].value("level", 1);
						unsigned int lastShot = jLevel[strI][strJ]["tower"].value("lastShot", 0);
						int featurePrice = jLevel[strI][strJ]["tower"].value("price", 100);
						double radius = jLevel[strI][strJ]["tower"].value("radius", 0);
						double damage = jLevel[strI][strJ]["tower"].value("damage", 0);
						double shotSpeed = jLevel[strI][strJ]["tower"].value("shotSpeed", 0);

						Feature* tmpFeature = new Feature(featurePrice, radius, damage, shotSpeed);
						DefaultTower* tmpTower = new DefaultTower(tmpFeature, strategies[strategyType]);
						Building* tmpBuilding = dynamic_cast<Building*>(tmpTower);

						playingField[i][j]->build(tmpBuilding);
					}
					else if (currBuilding == "castle") {
						json tmp = jLevel[strI][strJ]["castle"];

					}
				}
			}
		}
	}
	*/


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
