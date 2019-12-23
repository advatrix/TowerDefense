#include <thread>

#include "AppManager.h"





void AppManager::run() {
	window = new sf::RenderWindow(sf::VideoMode(200, 200), "Game");

	std::thread displayThread = std::thread(&AppManager::display, this);
	std::thread updThread = std::thread(&AppManager::update, this);


	displayThread.join();
	updThread.join();
}

void AppManager::start(unsigned int l) {
	game->load(l);
	run();
}

void AppManager::start(std::string level) {
	game->load(level);
	run();
}

void AppManager::display() {
	while (true) {
		if (m.try_lock()) {
			//update graphics
			std::vector<std::vector<TD::Cell*>> cells = game->getCells();

			for (auto it = cells.begin(); it != cells.end(); it++) {
				for (auto jt = it->begin(); jt != it->end(); jt++) {
					switch ((*jt)->getType()) {
					case TD::cellTypeEnum::forest: {
						sf::Image img;
						img.loadFromFile("textures/forest.png");
						sf::Texture texture;
						texture.loadFromImage(img);
						sf::Sprite sprite;
						sprite.setTexture(texture);
						sprite.setPosition((*jt)->cords().first * 32, (*jt)->cords().second * 32);
						window->draw(sprite);
					}
					}
				}
			}

			sf::Image img;
			img.loadFromFile("textures/current.png");
			sf::Texture texture;
			texture.loadFromImage(img);
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setPosition(currI * 32, currJ * 32);
			window->draw(sprite);

			sf::Event event;
			if (window->pollEvent(event)) {
				switch (event.type) {
				case sf::Event::KeyPressed: {
					switch (event.key.code) {
					case sf::Keyboard::Up:
						if (currI > 0) currI--;
						break;
					case sf::Keyboard::Down:
						if (currI < cells.size()) currI++;
						break;
					case sf::Keyboard::Left:
						if (currJ > 0) currJ++;
						break;
					case sf::Keyboard::Right:
						if (currJ < cells[0].size()) currJ++;
						break;
					}
				}
				}
			}
			//check for inputs
			m.unlock();
		}
		//wait for 30 milliseconds
	}
}

void AppManager::update() {
	while (true) {
		if (m.try_lock()) {
			game->update();
			m.unlock();
		}
	}
}