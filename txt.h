#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"
#include <string>
#include <cmath>

class TextObj {
private:
	sf::Font font;
	sf::Text text;
public:
	TextObj(float x, float y, int size, sf::Color color) {
		font.loadFromFile(RESOURSE + FONT);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(x, y);
	}
	void update(std::string str) { text.setString(str); }
	void draw(sf::RenderWindow& window) { window.draw(text); }
};