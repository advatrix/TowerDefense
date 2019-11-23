// TowerDefenseEditor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "IOFuncs.h"
//#include "..//TowerDefenseStaticLib/Landscape.h"
#include "..//TowerDefenseStaticLib/json.hpp"

using namespace IOFuncs;
using namespace nlohmann;

const char* menu[] = { "0. Quit", "1. Levels", "2. Enemies", "3. Other" };
const char* levelEditorMenu[] = { "0. Quit", "1. Load level", "2. Edit level", "3. Create level" };
const char* enemyEditorMenu[] = { "0. Quit", "1. Load enemy", "2. Edit enemy"};
const char* towerEditorMenu[] = { "0. Quit", "1. Load tower", "2. Edit tower"};
const char* strategies[] = { "0. Near to tower", "1. Near to castle", "2. Strong", "3. Weak", "4. Fast" };
const char* effects[] = { "0. Weakness", "1. Slowdown", "2. Poison" };
const char* buildings[] = { "0. Tower", "1. Magic Tower", "2. Lire", "3. Castle" };

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
			case 1:
				level[currI][currJ]["type"] = "road";
				int ans;
				print("Build a trap? 0/1");
				input(ans);
				if (ans) {
					level[currI][currJ]["trap"] = true;
					int type, value;
					print("input effect type");
					input(type);
					print("input effect value");
					input(value);
					level[currI][currJ]["trap"]["effect"]["value"] = value;
					level[currI][currJ]["trap"]["effect"]["type"] = type;
				}
				else level[currI][currJ]["trap"] = false;
				break;
			case 2:
				level[currI][currJ]["type"] = "field";
				print("Build something? 0/1");
				int ans;
				
				print("Build a lire? (0/1)");
				input(ans);
				if (ans) {
					int buildingType = dialog(buildings, NBuildings);
					switch (buildingType) {
					case tower: {
						level[currI][currJ]["building"] = "tower";
						int towerLevel, price, strategy;
						double radius, damage, shotSpeed;
						print("input level");
						input(level);
						print("input price");
						input(price);
						print("input strategy");
						input(strategy);
						print("damage");
						input(damage);
						print("radius");
						input(radius);
						print("shotSpeed");
						input(shotSpeed);
						level[currI][currJ]["building"]["level"] = level;
						level[currI][currJ]["building"]["price"] = price;
						level[currI][currJ]["building"]["strategy"] = strategy;
						level[currI][currJ]["building"]["damage"] = damage;
						level[currI][currJ]["building"]["radius"] = radius;
						level[currI][currJ]["building"]["shotSpeed"] = shotSpeed;
						break;
					}
					case magicTower: {
						level[currI][currJ]["building"] = "magicTower";
						int towerLevel, price, strategy, effect, value;
						double radius, damage, shotSpeed;
						unsigned int time;
						print("input effect");
						effect = dialog(effects, NEffects);
						print("input level");
						input(level);
						print("input price");
						input(price);
						print("input strategy");
						input(strategy);
						print("damage");
						input(damage);
						print("radius");
						input(radius);
						print("shotSpeed");
						input(shotSpeed);
						print("time");
						input(time);
						level[currI][currJ]["building"]["level"] = level;
						level[currI][currJ]["building"]["price"] = price;
						level[currI][currJ]["building"]["strategy"] = strategy;
						level[currI][currJ]["building"]["damage"] = damage;
						level[currI][currJ]["building"]["radius"] = radius;
						level[currI][currJ]["building"]["shotSpeed"] = shotSpeed;
						level[currI][currJ]["building"]["effect"] = effect;
						level[currI][currJ]["building"]["value"] = value;
						level[currI][currJ]["building"]["time"] = value;
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
							print("input speed");
							input(speed);
							print("input time");
							input(currTime);
							std::string currK = std::to_string(k);
							level[currI][currJ]["schedule"][currK]["enemy"]["title"] = title;
							level[currI][currJ]["schedule"][currK]["enemy"]["maxHp"] = maxHp;
							level[currI][currJ]["schedule"][currK]["enemy"]["currHp"] = maxHp;
							level[currI][currJ]["schedule"][currK]["enemy"]["speed"] = speed;
							level[currI][currJ]["schedule"][currK]["enemy"]["effect"] = false;
							level[currI][currJ]["schedule"][currK]["time"] = currTime;
						}
					}
					case castle: {
						if (isCastled) {
							isCastled = true;
							std::string title;
							int money;
							double hp;
						}
						else {
							print("The castle has been built already");
						}

					}
					}
				}
				else level[currI][currJ]["lire"] = false;
				break;
			}
		}
	}
	std::string filename = std::to_string(levelNo) + ".json";
	std::ofstream f(filename); 
	f << std::setw(4) << level << std::endl;
}

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

int main()
{
	int rc;
	while (rc = dialog(menu, NMenu)) menuFPtr[rc]();
	print("Program finished");
	return 0;
}
