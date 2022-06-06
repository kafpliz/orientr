#include "game.h"

Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ORIENT"),game_over(IMG + GAME_OVER), score_text(525, 10, 50, sf::Color::Yellow)
{
	//� ����� ���� ������ ������� �� ���� �����
	Platform* p1 = new Platform(0, WINDOW_HEIGHT - 55.f,
		WINDOW_WIDTH, 55.f);
	platform_sprites.push_back(p1);
	//���� 1-�� � �� 1/2 ������ �������
	Platform* p2 = new Platform(WINDOW_WIDTH / 4,
		WINDOW_HEIGHT * 3 / 4, WINDOW_WIDTH / 4, 55.f);
	platform_sprites.push_back(p2);
	Platform* p3 = new Platform(WINDOW_WIDTH * 2 / 3,
		WINDOW_HEIGHT / 2, WINDOW_WIDTH / 4, 55.f);
	platform_sprites.push_back(p3);
	window.setVerticalSyncEnabled(true);
	//meteor
	for (int i = 0; i < MTR_QTY; i++) {mtr[i].init(i * 150.f, -i * WINDOW_HEIGHT / 2.f);}
}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		// ������������ ����� �� �������� � ����� ������� ����?
		if (event.type == sf::Event::Closed)
			// ����� ��������� ���
			window.close();
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Space)
				if (game_state == GameState::SPLASH) game_state = GameState::PLAY;
	}
	//fireball
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() > 2) {
			fireball_sprites.push_back(new Fireball(player.getPosition().x +
				player.getWidth() / 2 - 5, player.getPosition().y));
			clock.restart();
		}
	}

}
void Game::update() {
	switch (game_state) {
	case GameState::SPLASH:
		break;
	case GameState::PLAY:
	{
		//meteor
		for (int i = 0; i < MTR_QTY; i++) {mtr[i].update();}

		for (auto it = fireball_sprites.begin(); it != fireball_sprites.end(); it++) { (*it)->update(); }
		map.update();
		score_text.update(std::to_string(score));
		player.update();
		for (auto iter = platform_sprites.begin();
			iter != platform_sprites.end(); iter++) {
			(*iter)->update();
		}
		//�������� ���� �������� ���� ���� ����� �������� �� �����
		if (player.getPosition().y <= WINDOW_HEIGHT / 3.f) {
			for (auto iter = platform_sprites.begin();
				iter != platform_sprites.end(); iter++) {
				(*iter)->setPosition((*iter)->getPosition().x,
					(*iter)->getPosition().y + abs(player.getSpeed().y));
				//���������, ������� ���������� ���� 4/3 ������ ������ 
				//�������� �� ��������
				if ((*iter)->getPosition().y > 4 * WINDOW_HEIGHT / 3) {
					(*iter)->setDel();
					score += 5;
				}

			}
		}
		//������� �������� ���������
		platform_sprites.remove_if([](Platform* p) {
			return p->getDel(); });
		while (platform_sprites.size() < PLATFORMS_QTY) {
			int len = rand() % 151 + 100;
			int new_x = rand() % (static_cast<int>(
				WINDOW_WIDTH - len));
			int new_y = rand() % 451 - 300;
			Platform* p = new Platform(new_x, new_y, len, 55.f);
			platform_sprites.push_back(p);
		}
		//death player
		if (player.getPosition().y >= WINDOW_HEIGHT) {
			game_state = GameState::GAME_OVER;
		}
		
		break;
	}
	case GameState::GAME_OVER:

		break;
	}
}
void Game::draw() {

	window.clear(BACKGROUND_COLOR);
	switch (game_state) {
	case GameState::SPLASH:
		break;
	case GameState::PLAY:
		//meteor
	for (int i = 0; i < MTR_QTY; i++) {window.draw(mtr[i].getSprite());}


		for (auto it = fireball_sprites.begin(); it != fireball_sprites.end(); it++) { (*it)->draw(window); }
		map.draw(window);
		score_text.draw(window);
		player.draw(window);
		for (auto iter = platform_sprites.begin();
			iter != platform_sprites.end(); iter++) {
			(*iter)->draw(window);
		}
		break;
	case GameState::GAME_OVER:
		game_over.draw(window);
		break;
	}
	window.display();
}
void Game::check_collisions() {
	for (auto iter = platform_sprites.begin();
		iter != platform_sprites.end(); iter++) {
		if (player.getSpeed().y > 0) {
			if (player.getHitBox().intersects((*iter)->getHitBox())) {
				if (player.getSpeed().y >= 0) {
					player.setIsJumping(false);
					player.resetSpeed();
					sf::Vector2f platform_pos = (*iter)->getPosition();
					sf::Vector2f player_new_pos =
						sf::Vector2f(player.getPosition().x,
							platform_pos.y - player.getHitBox().height);
					player.setPosition(player_new_pos);
				}
			}
		}



	}
	//game over 
	// position: meteor
	if (player.getHitBox().intersects(meteor.getHitBox())) {
			game_state = GameState::GAME_OVER;
		}


	
	//
	for (int i = 0; i < MTR_QTY; i++) {
		if (mtr[i].getHitBox().intersects(player.getHitBox())) {
			game_state = GameState::GAME_OVER;
		}
	}

}
