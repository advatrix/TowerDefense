#include "Menu.h"

Menu::Menu(unsigned int height, unsigned int width, std::vector<std::string> items_)
{
	for (auto it = items_.begin(); it != items_.end(); it++) {
		sf::Text tmp;
		tmp.setFillColor(sf::Color::White);
		tmp.setString(*it);
		font.loadFromFile("sansation.ttf");
		tmp.setFont(font);
		tmp.setPosition(sf::Vector2f(width / 2, height / (items_.size() * (items.size() + 1.))));
		items.push_back(tmp);
	}

	selectedItem = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (auto it = items.begin(); it != items.end(); it++)
		window.draw(*it);
}

void Menu::up()
{
	if (selectedItem >= 1) {
		items[selectedItem].setFillColor(sf::Color::White);
		--selectedItem;
		items[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::down()
{
	if (selectedItem < items.size() - 1) {
		items[selectedItem].setFillColor(sf::Color::White);
		++selectedItem;
		items[selectedItem].setFillColor(sf::Color::Red);
	}
}
