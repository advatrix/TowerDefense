#pragma once
#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"
#include "GraphicsManager.h"
#include "iofuncs.h"

using namespace TD;
using namespace IOFuncs; 

class AppManager
{
private:
	GameManager* game;
	GraphicsManager* graphics;
	std::string gameMenu[4] = { "0. Continue", "1. Pause", "2. Save & Quit", "3. Quit" };
	std::string lobby[4] = { "0. New game", "1. Load game", "2. Help", "3. Quit" };
	std::string pauseMenu[4] = { "0. Upgrade tower", "1. Build tower", "2. Game info", "3. Quit" };
	std::string newGameMenu[2] = { "0. Load level", "1. Create level" };

	std::string cellTypeMenu[3] = { "0. Forest", "1. Road", "2. Field" };

	void newGame();
	void loadGame();
	void help();
	void createLevel();
	void loadLevel();
	void play();

	void printLevelsList() {} //TODO
	void printSavesList() {} //TODO

public:
	void run();
	
	int menu(std::string vars[]);




};

