#include "fireball.h"
#include "settings.h"

Fireball::Fireball(float x, float y) {
	texture.loadFromFile(IMG + FIREBALL);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Fireball::update() {
	sprite.move(0.f, -FIREBALL_SPEEDY);
}
size_t Fireball::getWidth() { return sprite.getLocalBounds().width; }
size_t Fireball::getHeight() { return sprite.getLocalBounds().height; }
sf::FloatRect Fireball::getHitBox() { return sprite.getGlobalBounds(); }
void Fireball::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::Vector2f Fireball::getPosition() { return sprite.getPosition(); }