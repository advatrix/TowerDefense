#include <filesystem>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>

#include "AppManager.h"
#include "..//TowerDefenseStaticLib///TowerDefenseLib.h"

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

		for (unsigned j = 0; j < width; j++) {
			int cellType;
			std::cout << "enter type of cell" << i << ' ' << j;

			input(cellType);
			switch (cellType) {
			case cellTypeEnum::forest:
				cellsStructs.push_back(FileCell(i, j, cellTypeEnum::forest, 0, 0));
				break;
			case cellTypeEnum::road: {
				cellsStructs.push_back(FileCell(i, j, cellTypeEnum::road, 0, 0));
				break;
			case cellTypeEnum::field: {
				cellsStructs.push_back(FileCell(i, j, cellTypeEnum::field, 0, 0));
				break;
			}
			}
			}
		}
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
		cells[x][y].building = buildingTypeEnum::lire;
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
	castleFile << c;
	castleFile.close();


	cellsFile
}
