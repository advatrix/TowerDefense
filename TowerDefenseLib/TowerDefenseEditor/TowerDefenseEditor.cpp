// TowerDefenseEditor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <experimental/filesystem>
#include <filesystem>

#include "IOFuncs.h"
// #include "..//TowerDefenseStaticLib/Landscape.h"
#include "..//TowerDefenseStaticLib/json.hpp"

using namespace IOFuncs;
using namespace nlohmann;

namespace fs = std::experimental::filesystem;

typedef std::vector<std::string> Menu;

const char* menu[] = { "0. Quit", "1. Levels", "2. Enemies", "3. Other" };
const char* levelEditorMenu[] = { "0. Quit", "1. Load level", "2. Edit level", "3. Create level" };
const char* enemyEditorMenu[] = { "0. Quit", "1. Load enemy", "2. Edit enemy"};
const char* towerEditorMenu[] = { "0. Quit", "1. Load tower", "2. Edit tower"};
const char* strategies[] = { "0. Near to tower", "1. Near to castle", "2. Strong", "3. Weak", "4. Fast" };
const char* effects[] = { "0. Weakness", "1. Slowdown", "2. Poison" };
const char* buildings[] = { "0. Tower", "1. Magic Tower", "2. Lire", "3. Castle" };
const Menu cellTypeMenu = { "0. Forest", "1. Road", "2. Field" };
const Menu buildingsTypeMenu = { "0. Nothing", "1. Tower", "2. Magic Tower", "3. Lire", "4. Castle" };

const int NMenu = sizeof(menu) / sizeof(menu[0]);
const int NLevelEditorMenu = sizeof(levelEditorMenu) / sizeof(levelEditorMenu[0]);
const int NEnemyEditorMenu = sizeof(enemyEditorMenu) / sizeof(enemyEditorMenu[0]);
const int NTowerEditorMenu = sizeof(towerEditorMenu) / sizeof(towerEditorMenu[0]);
const int NBuildings = sizeof(buildings) / sizeof(buildings[0]);
const int NStrategies = sizeof(strategies) / sizeof(strategies[0]);
const int NEffects = sizeof(effects) / sizeof(effects[0]);

enum buildingsEnum {tower, magicTower, lire, castle};

void levelEditor();
void enemyEditor();
void towerEditor();

void loadLevel();
void editLevel();
void createLevel();

void loadEnemy();
void editEnemy();

void loadTower();
void editTower();

void (*menuFPtr[])() = { nullptr, levelEditor, enemyEditor, towerEditor };
void (*levelEditorFPtr[])() = { nullptr, loadLevel, editLevel, createLevel };
void (*enemyEditorFPtr[])() = { nullptr, loadEnemy, editEnemy };
void (*towerEditorFPtr[])() = { nullptr, loadTower, editTower };

int dialog(const char* msgs[], int N);
int dialog(const Menu& menu);

void levelEditor() {
	int rc;
	while (rc = dialog(levelEditorMenu, NLevelEditorMenu)) levelEditorFPtr[rc]();
}

void loadLevel() {
	print("not implemented yet");
	
	/*
	int n;
	print("input level number");
	input(n);
	
	try {
		TD::Landscape landscape(n);
	}
	catch (std::runtime_error& rte) {
		print(rte.what());
	}
	catch (std::invalid_argument& ia) {
		print(ia.what());
	}
	catch (std::exception& e) {
		print("---UNKNOWN EXCEPTION---");
		print(e.what());
	}
	*/

}

void createLevel() {
	int levelNo, height, width;
	bool isCastled = false;
	print("input level number");
	input(levelNo);
	print("input height (cells)");
	input(height);
	print("input width (cells)");
	input(width);
	json level;
	level["no"] = levelNo;
	level["height"] = height;
	level["width"] = width;
	for (int i = 0; i < height; i++) {
		std::string currI = std::to_string(i);
		for (int j = 0; j < width; j++) {
			std::string currJ = std::to_string(j);
			std::cout << "input cell " << i << j << " type";
			print("0: forest");
			print("1. road");
			print("2. field");
			int cellType;
			input(cellType);
			switch (cellType) {
			case 0:
				level[currI][currJ]["type"] = "forest";
				break;
			case 1: {
				level[currI][currJ]["type"] = "road";
				int ans;
				print("Build a trap? 0/1");
				input(ans);
				if (ans) {
					level[currI][currJ]["trap"] = "true";
					int type, value;
					print("input effect type");
					input(type);
					print("input effect value");
					input(value);
					std::string strType = std::to_string(type);
					std::string strValue = std::to_string(value);
					level[currI][currJ]["trap"]["effect"]["value"] = strValue;
					level[currI][currJ]["trap"]["effect"]["type"] = strType;
				}
				else level[currI][currJ]["trap"] = "false";
				break;
			}
			case 2: {
				level[currI][currJ]["type"] = "field";
				print("Build something? 0/1");
				int ans;
				input(ans);
				if (ans) {
					int buildingType = dialog(buildings, NBuildings);
					switch (buildingType) {
					case tower: {
						level[currI][currJ]["building"] = "tower";
						int towerLevel, price, strategy;
						double radius, damage, shotSpeed;
						print("input level");
						input(towerLevel);
						std::string strTowerLevel = std::to_string(towerLevel);
						print("input price");
						input(price);
						std::string strPrice = std::to_string(price);
						print("input strategy");
						input(strategy);
						std::string strStrategy = std::to_string(strategy);
						print("damage");
						input(damage);
						std::string strDamage = std::to_string(damage);
						print("radius");
						input(radius);
						std::string strRadius = std::to_string(radius);
						print("shotSpeed");
						input(shotSpeed);
						std::string strShotSpeed = std::to_string(shotSpeed);
						level[currI][currJ]["building"]["tower"]["level"] = strTowerLevel;
						level[currI][currJ]["building"]["tower"]["price"] = strPrice;
						level[currI][currJ]["building"]["strategy"] = strStrategy;
						level[currI][currJ]["building"]["damage"] = strDamage;
						level[currI][currJ]["building"]["radius"] = strRadius;
						level[currI][currJ]["building"]["shotSpeed"] = strShotSpeed;
						break;
					}
					case magicTower: {
						level[currI][currJ]["building"] = "magicTower";
						int towerLevel, price, strategy, effect, value;
						double radius, damage, shotSpeed;
						unsigned int time;
						print("input effect");
						effect = dialog(effects, NEffects);
						std::string strEffect = std::to_string(effect);
						print("input level");
						input(towerLevel);
						std::string strTowerLevel = std::to_string(towerLevel);
						print("input price");
						input(price);
						std::string strPrice = std::to_string(price);
						print("input strategy");
						input(strategy);
						std::string strStrategy = std::to_string(strategy);
						print("damage");
						input(damage);
						std::string strDamage = std::to_string(damage);
						print("radius");
						input(radius);
						std::string strRadius = std::to_string(radius);
						print("shotSpeed");
						input(shotSpeed);
						std::string strShotSpeed = std::to_string(shotSpeed);
						print("time");
						input(time);
						std::string strTime = std::to_string(time);
						print("input value");
						input(value);
						std::string strValue = std::to_string(value);
						level[currI][currJ]["building"]["level"] = strTowerLevel;
						level[currI][currJ]["building"]["price"] = strPrice;
						level[currI][currJ]["building"]["strategy"] = strStrategy;
						level[currI][currJ]["building"]["damage"] = strDamage;
						level[currI][currJ]["building"]["radius"] = strRadius;
						level[currI][currJ]["building"]["shotSpeed"] = strShotSpeed;
						level[currI][currJ]["building"]["effect"] = strEffect;
						level[currI][currJ]["building"]["value"] = strValue;
						level[currI][currJ]["building"]["time"] = strTime;
						break;
					}
					case lire: {
						level[currI][currJ]["building"] = "lire";
						int enemiesCount;
						unsigned int currTime;
						print("enter enemies count");
						input(enemiesCount);
						for (int k = 0; k < enemiesCount; k++) {
							std::cout << "input enemy " << k + 1 << " parameters";
							std::string title;
							double maxHp, speed;
							print("input title");
							input(title);
							print("input max hp");
							input(maxHp);
							std::string strMaxHp = std::to_string(maxHp);
							print("input speed");
							input(speed);
							std::string strSpeed = std::to_string(speed);
							print("input time");
							input(currTime);
							std::string strTime = std::to_string(currTime);
							std::string currK = std::to_string(k);
							level[currI][currJ]["schedule"][currK]["enemy"]["title"] = title;
							level[currI][currJ]["schedule"][currK]["enemy"]["maxHp"] = strMaxHp;
							level[currI][currJ]["schedule"][currK]["enemy"]["currHp"] = strMaxHp;
							level[currI][currJ]["schedule"][currK]["enemy"]["speed"] = strSpeed;
							level[currI][currJ]["schedule"][currK]["enemy"]["effect"] = "false";
							level[currI][currJ]["schedule"][currK]["time"] = strTime;
						}
					}
					case castle: {
						if (isCastled) {
							isCastled = true;
							std::string title;
							int money;
							double hp;
							print("enter title");
							input(title);
							print("enter money");
							input(money);
							std::string strMoney = std::to_string(money);
							print("enter hp");
							input(hp);
							std::string strHp = std::to_string(hp);
							level[currI][currJ]["building"] = "castle";
							level[currI][currJ]["castle"]["title"] = title;
							level[currI][currJ]["castle"]["money"] = strMoney;
							level[currI][currJ]["castle"]["hp"] = strHp;
						}
						else {
							print("The castle has been built already");
						}

					}
					}
				}
				break;
			}
			}
		}
	}
	std::string filename = std::to_string(levelNo) + ".json";
	std::ofstream f(filename); 
	f << std::setw(4) << level << std::endl;
}
/*
void createLevel() {
	int levelNo, height, width;
	bool castled = false;
	print("input level number");
	input(levelNo);
	print("input height");
	input(height);
	print("input width");
	input(width);

	// create a level directory
	std::string dirName = std::to_string(levelNo);
	fs::path p = "/" + dirName;
	fs::create_directory(p);
	fs::current_path(p);




	int effectsCounter = 0, buildingsCounter = 0;
	std::vector<TD::FileCell> cells;
	std::vector<TD::FileEnemy> enemies;
	std::vector<TD::FileTower> towers;
	std::vector<TD::FileLire> lires;
	std::vector<TD::FileEffect> effects;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << "CELL " << i << " " << j << std::endl;
			print("Set a type of a cell");
			print("0. Forest");
			print("1. Road");
			print("2. Field");
			int cellType;
			input(cellType);
			switch (cellType) {
			case TD::cellTypeEnum::forest: {
				cells.push_back(TD::FileCell(i, j, cellType, TD::buildingTypeEnum::none, 0));
				break;
			} 
			case TD::cellTypeEnum::field: {
				print("Set a type of a building");
				int building = dialog(buildingsTypeMenu);
				switch (building) {
				case TD::buildingTypeEnum::none: {
					cells.push_back(TD::FileCell(i, j, cellType, TD::buildingTypeEnum::none, 0));
					break;
				} 
				case TD::buildingTypeEnum::castle: {
					if (castled) {
						print("The castle has already been built. This cell will be empty");
						cells.push_back(TD::FileCell(i, j, cellType, TD::buildingTypeEnum::none, 0));
					}
					else {
						castled = true;
						int x, y, money;
						double maxHp, curHp;
						std::string title;
						print("Input castle features");
						print("Input title");
						input(title);
						print("input money");
						input(money);
						print("input maxHp");
						input(maxHp);
						print("input curHp");
						input(curHp);
						cells.push_back(TD::FileCell(i, j, cellType, building, 0));
						TD::FileCastle castle_(x, y, money, title, maxHp, curHp); // мб и не нужно совсем
						std::ofstream castleFile("castle");
						castleFile << x << y << money << title << maxHp << curHp << std::endl;
					}
					}
				}
				}
			}
			}

		}
	}

}
*/

void enemyEditor() {
	print("not implemented yet");
}

void towerEditor() {
	print("not implemented yet");
}

void editLevel() {
	print("not implemented yet");
}

void loadEnemy() {
	print("not implememted yet");
}

void editEnemy() {
	print("not implemented yet");
}

void loadTower() {
	print("not implemented yet");
}

void editTower() {
	print("not implemented yet");
}

/*
void createLevel() {
	int n, height, width, nLires;
	print("input level no");
	input(n);
	print("input height (cells)");
	input(height);
	print("input width (cells)");
	input(width);
	
}*/

int dialog(const char* msgs[], int N) {
	int rc;
	do {
		for (int i = 0; i < N; i++) puts(msgs[i]);
		puts("Make your choice: -->");
		input(rc);
		if (rc >= 0 && rc < N) continue;
		puts("I don't understand you. Try again");
	} while (rc < 0 || rc > N);
	return rc;
}

int dialog(const Menu & menu) {
	int rc;
	do {
		for (Menu::size_type i = 0; i < menu.size(); ++i) std::cout << menu[i] << '\n';
		print("Make your choice");
		input(rc);
		if (rc >= 0 && rc < static_cast<int>(menu.size())) continue;
		print("Incorrect choice. Try again");
	} while (rc < 0 || rc > static_cast<int>(menu.size()));
	return rc;

}

int main()
{
	int rc;
	while (rc = dialog(menu, NMenu)) menuFPtr[rc]();
	print("Program finished");
	return 0;
}
