// #include "..\TowerDefenseGUI\AppManager.h"
#include <filesystem>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <conio.h>

#include "AppManager.h"


#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"

using namespace TD;

void AppManager::run() {
	setFontSize(25);
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
	try {
		game = new GameManager(filename);
	}
	catch (std::exception & e) {
		std::cout << "Something went wrong: " << e.what() << std::endl;
		print("Press any key to continue");
		getch();
		return;
	}
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
		schedulesFile << static_cast<unsigned>((*it).size()) << std::endl;
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

	//std::experimental::filesystem::current_path("../");
	// std::experimental::filesystem::current_path("../");
	//game->load(levelName);
	//play();
}

void AppManager::help() {
	std::cout << "This is a console version of Tower Defense Game.\n\
		Hope you'll enjoy\n";
	getch();
}

void AppManager::loadLevel() {
	unsigned int filename;
	print("input level number");
	input(filename);
	try {
		game->load(filename);
	}
	catch (std::exception& e) {
		std::cout << "Something went wrong: " << e.what() << std::endl;
		print("Press any key to continue");
		getch();
		return;
	}
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
		displayGameState();
		if (game->getHp() == 0) {
			std::cout << "You lose" << std::endl;
			return;
		}
		if (game->getTime() % 13 == 0 || game->getTime() == 3) {

			for (int i = 0; i < gameMenu.size(); i++)
				print(gameMenu[i]);
			char rc = getch();
			switch (rc) {
			case '1':
				system("CLS");
				pause();
				break;
			case '2':
				system("CLS");
				save();
				return;
			case '3':
				return;
			case '4': {
				std::string ans;
				input(ans);
				if (ans == "hesoyam" || ans == "mephi") {
					Castle* c = game->getCastle();
					c->setMaxHp(9000);
					c->incHp(9000 - c->getCurHp());
					c->incMoney(100500 - c->getMoney());
				}
				break;
			}
			}
		}
		else {
			for (int i = 0; i < gameMenu.size(); i++)
				print(gameMenu[i]);
			char rc = getch();
			switch (rc) {
			case '1': 
				system("CLS");
				pause();
				break;
			case '2':
				system("CLS");
				save();
				return;
			case '3':
				return;
			}
			/*int rc = menu(gameMenu);
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
			*/
		}
		system("CLS");
	}
}

void AppManager::displayGameState() const {
	std::cout << "Current turn: " << game->getTime() << std::endl
		<< "LIVES: " << game->getHp() << std::endl
		<< "MONEY: " << game->getMoney() << std::endl;
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
			setStrategy();
			break;
		default: return;
		}
	}
}

void AppManager::setStrategy() {
	print("Input Tower's cords");
	int x, y;
	print("input x");
	input(x);
	print("input y");
	input(y);
	int rc = menu(strategyTypeMenu);
	// game->setStrategy(x, y, static_cast<strategyTypeEnum>(rc));
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
	std::cout << *graphics;
	print("input tower cords");
	int x, y;
	print("input x");
	input(x);
	print("input y");
	input(y);
	try {
		game->upgrade(x, y);
	}
	catch (std::runtime_error & e) {
		print(e.what());
	}
}

void AppManager::build() {
	std::cout << *graphics << std::endl;
	std::cout << "Your money: " << game->getMoney() << std::endl;
	Feature* f = game->getFeature(0);
	std::cout << "TOWER" << std::endl <<
		"PRICE: " << f->getPrice() << std::endl <<
		"DAMAGE: " << f->getDamage() << std::endl <<
		"RADIUS: " << f->getRadius() << std::endl <<
		"SHOT SPEED: " << f->getShotSpeed() << std::endl;
	std::cout << std::endl << "Magic effects cost Value multiplied by Time";
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
		try {
			game->buildTower(x, y, 1);
		}
		catch (std::runtime_error& e) {
			print(e.what());
		}
		break;
	case 1: {
		int effType = menu(effTypeMenu);
		print("enter effect params");
		print("enter value");
		unsigned value, t;
		input(value);
		print("input time");
		input(t);
		try {
			game->buildMagicTower(x, y, 1, static_cast<effectTypeEnum>(effType), value, t);
		}
		catch (std::runtime_error& e) {
			print(e.what());
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
		try {
			game->buildTrap(x, y, static_cast<effectTypeEnum>(effType), value, t);
		}
		catch (std::runtime_error& e) {
			print(e.what());
		}
		break;
	}
	}
}

void AppManager::info() const {
	std::cout << "HP: " << game->getHp() << "\nMoney: " << game->getMoney() << std::endl;
	print("input cell you want to get info about");
	int x, y;
	print("input x");
	input(x);
	print("input y");
	input(y);
	Cell* c = game->getCells()[x][y];
	std::cout << "Type: " << c->getType() << std::endl;

}




