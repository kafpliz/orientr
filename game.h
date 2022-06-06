#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "player.h"
#include "platform.h"
#include "splash.h"
#include "txt.h"
#include "map.h"
#include "fireball.h"
#include "meteor.h"
class Game {
public:
	enum class GameState { SPLASH, PLAY, GAME_OVER };
	Game();
	void play();

private:
	sf::RenderWindow window;
	GameState game_state = GameState::PLAY;
	Player player;
	Meteor meteor;
	std::list<Platform*> platform_sprites;


	std::list<Fireball*> fireball_sprites;
	Splash game_over ;
	Map map;
	Meteor mtr[MTR_QTY];


	int score = 0;
	TextObj  score_text;
	sf::Clock clock;



	void check_events();
	void update();
	void draw();
	void check_collisions();

};