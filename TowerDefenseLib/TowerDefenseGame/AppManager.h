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
	std::vector<std::string> gameMenu = { "0. Continue", "1. Pause", "2. Save & Quit", "3. Quit" };
	std::vector<std::string> lobby = { "0. New game", "1. Load game", "2. Help", "3. Quit" };
	std::vector<std::string> pauseMenu = { "0. Upgrade tower", "1. Build tower", "2. Game info","3. Set Tower's strategy", "4. Quit" };
	std::vector<std::string> newGameMenu = { "0. Load level", "1. Create level" };

	std::vector<std::string> cellTypeMenu = { "0. Forest", "1. Road", "2. Field" };
	std::vector<std::string> towerTypeMenu = { "0. Tower", "1. Magic Tower", "2. Trap" };
	std::vector<std::string> effTypeMenu = { "0. Weakness", "1. Slowdown", "2. Poison" };

	std::vector<std::string> strategyTypeMenu = { "0. Nearest to tower", "1. Nearest to castle", "2. Strongest",
	"3. Weakest", "4. Fastest" };

	void newGame();
	void loadGame();
	void help();
	void createLevel();
	void loadLevel();
	void play();

	void pause();
	void save();
	void upgrade();
	void build();
	void setStrategy();
	void info() const;

	void printLevelsList() {} //TODO
	void printSavesList() {} //TODO

public:
	void run();
	
	int menu(std::vector<std::string> v);

	AppManager() {
		game = new GameManager();
		graphics = new GraphicsManager();
	}

	void displayGameState() const;



};

