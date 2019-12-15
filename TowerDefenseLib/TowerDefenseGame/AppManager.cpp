#include <filesystem>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "AppManager.h"


#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"

using namespace TD;

void AppManager::run() {
	while (true) {
		int rc = menu(lobby);
		switch (rc) {
		case 0:
			newGame();
			break;
		case 1:
			loadGame();
			break;
		case 2:
			help();
			break;
		default:
			return;
		}
		system("CLS");
	}
}

void AppManager::newGame() {
	print("Starting a new game");
	int rc = menu(newGameMenu);
	switch (rc) {
	case 0:
		loadLevel();
		break;
	case 1:
		createLevel();
		break;
	default:
		return;
	}
}

void AppManager::loadGame() {
	print("enter filename");
	std::string filename;
	input(filename);
	game = new GameManager(filename);
	play();
}

void AppManager::createLevel() {
	unsigned height, width;
	std::string levelName;
	print("input level name");
	input(levelName);
	std::experimental::filesystem::current_path("../levels");
	std::experimental::filesystem::create_directory(levelName);
	std::experimental::filesystem::current_path(levelName);

	std::fstream cellsFile("cells.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		enemiesFile("enemies.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		towersFile("towers.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		liresFile("lires.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		effectsFile("effects.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		trapsFile("traps.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		schedulesFile("schedules.bin", std::ios::binary | std::ios::out | std::ios::trunc),
		featuresFile("features.bin", std::ios::binary | std::ios::out | std::ios::trunc);

	std::vector<FileCell> cellsStructs;
	std::vector<FileEnemy> enemiesStructs;
	std::vector<FileTower> towerStructs;
	std::vector<FileLire> liresStructs;
	std::vector<FileEffect> effectsStructs;
	std::vector<FileTrap> trapsStructs;
	std::vector<std::vector<FileScheduleItem>> schedulesStructs;



	print("enter map size:");
	print("enter height");
	input(height);
	print("enter width");
	input(width);



	std::vector<std::vector<FileCell>> cells;
	for (unsigned i = 0; i < height; i++) {
		std::vector<FileCell> row;
		for (unsigned j = 0; j < width; j++) {
			int cellType;
			std::cout << "enter type of cell" << i << ' ' << j;

			input(cellType);
			switch (cellType) {
			case cellTypeEnum::forest:
				row.push_back(FileCell(i, j, cellTypeEnum::forest, 0, 0));
				break;
			case cellTypeEnum::road: 
				row.push_back(FileCell(i, j, cellTypeEnum::road, 0, 0));
				break;
			case cellTypeEnum::field: {
				row.push_back(FileCell(i, j, cellTypeEnum::field, 0, 0));
				break;
			}

			}

		}
		cells.push_back(row);
	}

	std::vector<FileFeature> featuresStructs;
	int levelCount;
	print("how many tower levels?");
	input(levelCount);
	for (int i = 0; i < levelCount; i++) {
		double dmg, shotSpeed, rad;
		int price;
		print("enter damage");
		input(dmg);
		print("enter shotSpeed");
		input(shotSpeed);
		print("enter radius");
		input(rad);
		print("input price");
		input(price);
		featuresStructs.push_back(FileFeature(i + 1, price, dmg, rad, shotSpeed));
	}

	std::vector<std::vector<FileScheduleItem>> schedule;

	print("how many lires?");
	int lc;
	input(lc);
	for (int i = 0; i < lc; i++) {
		int x, y;
		print("enter cords");
		print("enter x");
		input(x);
		print("enter y");
		input(y);
		print("how many enemies?");
		int ec;
		input(ec);
		liresStructs.push_back(FileLire(x, y, ec));
		cells[x][y].building = 4;
		// cells[x][y].building = buildingTypeEnum::lire;
		cells[x][y].buildingId = i;
		std::vector<FileScheduleItem> tmpSch;
		for (int j = 0; j < ec; j++) {
			std::cout << "creating enemy " << j + 1 << std::endl;
			unsigned int time;
			std::string title;
			double hp, speed;
			int money;
			print("input spawn time");
			input(time);
			print("input title");
			input(title);
			print("input hp");
			input(hp);
			print("input speed");
			input(speed);
			print("input money");
			input(money);
			tmpSch.push_back(FileScheduleItem(time, title, hp, speed, money));
		}
		schedule.push_back(tmpSch);
	}

	print("Creating a castle");
	int x, y, money;
	std::string title;
	double mhp, chp;
	print("input x");
	input(x);
	print("input y");
	input(y);
	print("input start money");
	input(money);
	print("input title");
	input(title);
	print("input current hp");
	input(chp);
	print("input max hp");
	input(mhp);

	FileCastle c(x, y, money, title, mhp, chp);
	std::fstream castleFile("castle.bin", std::ios::binary | std::ios::out | std::ios::trunc);
	castleFile << c << std::endl;
	castleFile.close();

	cellsFile << height << std::endl << width << std::endl;
	for (auto it = cells.begin(); it != cells.end(); it++) {
		for (auto jt = (*it).begin(); jt != (*it).end(); jt++) {
			cellsFile << (*jt);
		}
	}

	liresFile << static_cast<unsigned>(liresStructs.size()) << std::endl;
	for (auto it = liresStructs.begin(); it != liresStructs.end(); it++) {
		liresFile << (*it);
	}

	schedulesFile << static_cast<unsigned>(schedule.size()) << std::endl;
	for (auto it = schedule.begin(); it != schedule.end(); it++) {
		schedulesFile << static_cast<unsigned>((*it).size());
		for (auto jt = (*it).begin(); jt != (*it).end(); jt++) schedulesFile << (*jt);
	}

	size_t featuresCount = featuresStructs.size();
	featuresFile << featuresCount << std::endl;
	for (auto it = featuresStructs.begin(); it != featuresStructs.end(); it++) featuresFile << (*it);

	cellsFile.close();
	enemiesFile.close();
	towersFile.close();
	liresFile.close();
	effectsFile.close();
	trapsFile.close();
	schedulesFile.close();
	featuresFile.close();

	std::experimental::filesystem::current_path("../");
	// std::experimental::filesystem::current_path("../");
	game->load(levelName);
	play();
}

void AppManager::help() {
	print("not implemented yet");
}

void AppManager::loadLevel() {
	std::string filename;
	print("input filename");
	input(filename);
	game->load(filename);
	play();
}

void AppManager::play() {
	int rc;
	graphics = new GraphicsManager(game->getCells(), game->getEnemyTable());
	while (true) {
		game->update();
		graphics->update(game->getEnemyTable());
		graphics->render();
		std::cout << *graphics;
		int rc = menu(gameMenu);
		switch (rc) {
		case 1: 
			pause();
			break;
		case 2:
			save();
			return;
		case 3:
			return;
		}
		system("CLS");
	}
}


void AppManager::pause() {
	while (true) {
		int rc = menu(pauseMenu);
		switch (rc) {
		case 0:
			upgrade();
			break;
		case 1:
			build();
			break;
		case 2:
			info();
			break;
		case 3:
			return;
		}
	}
}

int AppManager::menu(std::vector<std::string> v) {
	for (int i = 0; i < v.size(); i++) print(v[i]);
	int rc;
	input(rc);
	system("CLS");
	return rc;
}

void AppManager::save() {
	game->save();
}

void AppManager::upgrade() {
	print("input tower cords");
	int x, y;
	print("input x");
	input(x);
	print("input y");
	input(y);
	game->upgrade(x, y);
}

void AppManager::build() {
	print("input cords");
	int x, y;
	print("input x");
	input(x);
	print("input y");
	input(y);
	print("enter tower type");
	int type = menu(towerTypeMenu);
	switch (type) {
	case 0:
		game->buildTower(x, y, 1);
		break;
	case 1: {
		int effType = menu(effTypeMenu);
		print("enter effect params");
		print("enter value");
		unsigned value, t;
		input(value);
		print("input time");
		input(t);
		switch (effType) {
		case 0:
			game->buildMagicTower(x, y, 1, effectTypeEnum::slowdown, value, t);
			break;
		case 1:
			game->buildMagicTower(x, y, 1, effectTypeEnum::weakness, value, t);
			break;
		case 2:
			game->buildMagicTower(x, y, 1, effectTypeEnum::poison, value, t);
			break;
		}
		break;
	}
	case 2: {
		int effType = menu(effTypeMenu);
		print("enter effect params");
		print("enter value");
		unsigned value, t;
		input(value);
		print("input time");
		input(t);
		switch (effType) {
		case 0:
			game->buildTrap(x, y, effectTypeEnum::slowdown, value, t);
			break;
		case 1:
			game->buildTrap(x, y, effectTypeEnum::weakness, value, t);
			break;
		case 2:
			game->buildTrap(x, y, effectTypeEnum::poison, value, t);
			break;
		}
		break;
	}
	}
}

void AppManager::info() const {
	std::cout << "HP: " << game->getHp() << "\nMoney: " << game->getMoney() << std::endl;
}




