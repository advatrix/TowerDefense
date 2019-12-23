#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "AppManager.h"

#include "IOFuncs.h"

#include <iostream>
#include <conio.h>

using namespace IOFuncs;

int main()
{
	/*
	sf::RenderWindow window(sf::VideoMode(200, 200), "Tower Defense - Magic Weapon", sf::Style::Fullscreen);
	std::string playStr = "Play";
	std::string aboutStr = "About";
	std::string quitStr = "Quit";
	std::vector<std::string> m;
	m.push_back(playStr);
	m.push_back(aboutStr);
	m.push_back(quitStr);
	Menu menu(window.getSize().x, window.getSize().y, m);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed: {
				switch (event.key.code) {
				case sf::Keyboard::Up:
					menu.up();
					break;
				case sf::Keyboard::Down:
					menu.down();
					break;
				case sf::Keyboard::Enter: {
					unsigned int res = menu.getItem();
					switch (res) {
					case 0:
						
					}
					break;
				}
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
				window.close();
				break;
			}
		}

		window.clear();
		menu.draw(window);
		window.display();
	}*/
	AppManager app;
	std::cout << "0. Play" << std::endl <<  "1. About" << std::endl <<  "2. Quit" << std::endl;
	int ans;
	input(ans);
	switch (ans) {
	case 0: {
		print("0. Load");
		print("1. New");
		int ans1;
		input(ans1);
		switch (ans1) {
		case 0: {
			print("input level name");
			std::string levelname;
			input(levelname);
			AppManager app;
			app.start(levelname);
			break;
		}
		case 1: {
			print("input level no");
			int n;
			input(n);
			AppManager app;
			app.start(n);
			break;
		}
				break;
		}
	}
	case 1: {
		print("Some info about the game");
		break;
	}
	default:
		break;

	}



	return 0;
}