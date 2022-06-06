#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"
#include <string>

class Splash {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Splash(std::string file_name) {
		texture.loadFromFile(file_name);
		sprite.setTexture(texture);
	}
	void draw(sf::RenderWindow& window) { window.draw(sprite); }
};