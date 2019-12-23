#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>


class Menu
{
private:
	std::vector<sf::Text> items;
	unsigned int selectedItem;

	sf::Font font;


public:
	Menu(unsigned int height, unsigned int width, std::vector<std::string> items_);
	~Menu() {}

	void draw(sf::RenderWindow& window);

	void up();
	void down();

	inline unsigned int getItem() const { return selectedItem; }

};

