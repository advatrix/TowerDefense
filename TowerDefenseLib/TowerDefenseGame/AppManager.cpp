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

	std::vector<std::vector<Cell*>> cells;
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
}
