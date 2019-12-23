#pragma once

#include <mutex>

#include <SFML/Graphics.hpp>
#include "../TowerDefenseStaticLib/TowerDefenseLib.h"
class AppManager
{
private:

	std::mutex m;

	TD::GameManager* game;
	sf::RenderWindow* window;

	void display();
	void update();

	unsigned int currI;
	unsigned int currJ;

public:
	void run();
	void start(unsigned int level);
	void start(std::string filename);
	

	// void menu();

	AppManager():
	currI(0), currJ(0) 
	{
		game = new TD::GameManager;
		// window = new sf::RenderWindow(sf::VideoMode(200, 200), "Game");
	}

	
	
};

