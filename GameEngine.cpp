#include "GameEngine.h"

//main function
void GameEngine::loop() {
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
					for (auto& el : buttons) {
						if (el.mouse_click(mouse_pos)) {
							activeScene = el.executre();
						}
					}
					if (activeScene == scene::LEVELS) {
						for (auto& el : levels_buttons) {
							if (el.mouse_click(mouse_pos)) {
								activeLevel = el.executre();
							}
						}
					}
					else if (activeScene == scene::SKINS) {
						for (auto& el : skins_buttons) {
							if (el.mouse_click(mouse_pos)) {
								player->setSkin(el.executre());
							}
						}
					}

				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					player->shoot(bullets);
				}
			}
		}

		elapsed = clock.getElapsedTime();
		clock.restart();

		select_buttons();
		hover();
		if (activeScene == scene::PLAY) {
			removeObj();
		}

		draw(elapsed);
	}
}

//display sprites and buttons 
void GameEngine::draw(sf::Time& time) {
	window.clear(sf::Color::Black);
	scene_select(time);
	for (auto& el : buttons) window.draw(el);
	window.display();
}

//changing active scene
void GameEngine::scene_select(sf::Time& time) {
	switch (activeScene)
	{
	case scene::PLAY:
		play(time);
		break;
	case scene::SKINS:
		skins(time);
		break;
	case scene::EXIT:
		window.close();
		break;
	case scene::MENU:
		menu(time);
		break;
	case scene::LEVELS:
		levels(time);
		break;
	case scene::LOADING:
		loading_level_second_stage();
		activeScene = scene::PLAY;
		break;
	case scene::GAME_OVER:
		game_over();
		break;
	case scene::AUTHOR:
		break;
	default:
		break;
	}
}

//sets outline on button-text
void GameEngine::hover() {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	for (auto& el : buttons) {
		el.hover(mouse_pos);
	}
	if (activeScene == scene::LEVELS) {
		for (auto& el : levels_buttons) {
			el.hover(mouse_pos);
		}
	}
	else if (activeScene == scene::SKINS) {
		for (auto& el : skins_buttons) {
			el.hover(mouse_pos);
		}
	}
}

//select specific buttons to diffrent scenes
void GameEngine::select_buttons() {
	switch (activeScene)
	{
	case scene::PLAY:
		buttons.clear();
		buttons.shrink_to_fit();
		break;
	case scene::MENU:
		buttons.clear();
		buttons.shrink_to_fit();
		buttons.emplace_back(Button<scene>("Levels", font, 50, sf::Vector2f(300, 500), scene::LEVELS));
		buttons.emplace_back(Button<scene>("Skins", font, 50, sf::Vector2f(300, 600), scene::SKINS));
		buttons.emplace_back(Button<scene>("Exit", font, 50, sf::Vector2f(300, 700), scene::EXIT));
		break;
	case scene::SKINS:
		buttons.clear();
		buttons.shrink_to_fit();
		buttons.emplace_back(Button<scene>("Menu", font, 50, sf::Vector2f(300, 700), scene::MENU));
		skins_buttons.clear();
		skins_buttons.shrink_to_fit();
		skins_buttons.emplace_back(Button<SkinType>("SKIN 1", font, 50, sf::Vector2f(300, 600), SkinType::HERO_1));
		skins_buttons.emplace_back(Button<SkinType>("SKIN 2", font, 50, sf::Vector2f(600, 600), SkinType::HERO_2));
		skins_buttons.emplace_back(Button<SkinType>("SKIN 3", font, 50, sf::Vector2f(900, 600), SkinType::HERO_3));
		break;
	case scene::LEVELS:
		buttons.clear();
		buttons.emplace_back(Button<scene>("Play", font, 50, sf::Vector2f(300, 600), scene::LOADING));
		buttons.emplace_back(Button<scene>("Back to Menu", font, 50, sf::Vector2f(600, 600), scene::MENU));
		break;
	case scene::GAME_OVER:
		buttons.clear();
		buttons.emplace_back(Button<scene>("Back To Menu", font, 50, sf::Vector2f(0, 0), scene::MENU));
		buttons[0].setPosition(window.getSize().x / 2 - buttons[0].getGlobalBounds().width / 2, 600);
		break;

	}
}
//play scene function
void GameEngine::play(sf::Time& time) {
	generateBonus(time);
	player->animation(time);
	window.draw(*player);
	for (auto& el : obj) {
		el->animation(elapsed);
		if (typeid(*el) == typeid(Spaceship)) dynamic_cast<Spaceship&>(*el).shoot(bullets);
		window.draw(*el);
	}
	for (auto& el : bullets) {
		el->animation(elapsed);
		window.draw(*el);
	}
	bar->show(window);
	bar->setLive(player->getLife());
	bar->setBonus(player->getBulletType());
	if (player->getLife() <= 0) {
		delete bar;
		activeScene = scene::GAME_OVER;
	}
	else {
		bool test = 1;
		for (auto& el : obj) if (typeid(*el) == typeid(Spaceship)) test = 0;
		if (test) {
			delete bar;
			activeScene = scene::GAME_OVER;
		}
	}
}

//menu scene function
void GameEngine::menu(sf::Time& time) {
	window.draw(gameTitle);
}


//skins scene function
void GameEngine::skins(sf::Time& time) {
	for (auto& el : skins_buttons) window.draw(el);
	player->setPosition(window.getSize().x / 2 - player->getGlobalBounds().width / 2, window.getSize().y / 2);
	window.draw(*player);
}

//level picking scene function
void GameEngine::levels(sf::Time& time) {
	for (auto& el : levels_buttons) window.draw(el);
}

//end of the game function
void GameEngine::game_over() {
	obj.clear();
	bullets.clear();
	window.draw(gameOverText);
}

//first stage of loading levels from file
void GameEngine::loading_level_first_stage() {
	ifstream file(this->levels_path);
	std::string tmp;
	int counter = 0;
	while (file >> tmp) {
		levels_buttons.emplace_back(Button<string>("Level" + to_string(counter + 1), font, 50, sf::Vector2f(100 + 270 * counter, 200), tmp));
		++counter;
	}
}

//second stage of loading levels from file
void GameEngine::loading_level_second_stage() {
	level = Level(activeLevel, font, 25, player->getLife());
	obj = level.load_level(window.getSize());
	bar = level.getStatusBar();
	player->setLife(4);
	player->setPosition(player->getStartPosition());
}

//generate bonus objects
void GameEngine::generateBonus(sf::Time& time) {
	if (time_counter > 7) {
		if (rand() % 100 < 100) {

			obj.emplace_back(std::make_unique<Bonus>("images/presents.png", sf::Vector2f(rand() % window.getSize().x, 0), 0));
		}
		time_counter = 0;
	}
	else time_counter += time.asSeconds();
}
//zarzadzanie kolizja

void GameEngine::collision_management(AnimatedSprite& obj1, AnimatedSprite& obj2) {
	if (obj1.colision(obj2)) {
		//PLAYER vs ENEMY/BARRYCADE (COLISION)
		if (obj1.getControllable() && (typeid(obj2) == typeid(Spaceship) || typeid(obj2) == typeid(Barricade))) {
			dynamic_cast<Spaceship&>(obj1).setObjToDefaultPosition();
			obj1.setLife(obj1.getLife() - 1);
			obj2.setLife(0);

		}
		//PLAYER vs BONUS (COLISION)
		else if (obj1.getControllable() && obj2.getIsBonus()) {
			BulletType tmp = dynamic_cast<Bonus&>(obj2).getBulletType();
			dynamic_cast<Spaceship&>(obj1).setBulletType(tmp);
			//bar->setBonus(tmp);
			obj2.setLife(0);
		}
		//PLAYER vs BULLET(ENEMY)
		else if (obj1.getControllable() && (!obj2.getControllable() && !obj2.getIsBonus())) {
			obj1.setLife(obj1.getLife() - 1);
			obj2.setLife(obj2.getLife() - 1);
		}
		//ENEMY,BARRYCADE vs BULLET(HERO)
		else if ((!obj1.getControllable() || obj1.getPasive()) && obj2.getControllable()) {
			obj1.setLife(obj1.getLife() - 1);
			obj2.setLife(obj2.getLife() - 1);

		}
		//BARRYCADE vs BULLET(ENEMY)
		else if (obj1.getPasive() && !obj2.getControllable()) {
			obj1.setLife(obj1.getLife() - 1);
			obj2.setLife(obj2.getLife() - 1);
		}
	}
}


//Objects remove function
void GameEngine::removeObj() {
	//[PLAYER OBJ]
	for (auto& el : obj) collision_management(*player, *el);
	//[PLAYER BULLETS]
	for (auto& el : bullets) collision_management(*player, *el);
	//[OBJ BULLETS]
	for (auto& el : obj) {
		for (auto& ell : bullets) {
			collision_management(*el, *ell);
		}
	}

	//DELETE OBJECTS
	auto it = obj.begin();
	while (it != obj.end()) {
		if ((**it).getLife() <= 0) {
			if (typeid(Spaceship) == typeid(**it)) bar->addEnemies();

			it = obj.erase(it);
		}
		else ++it;
	}
	obj.shrink_to_fit();

	//DELETE BULLETS
	auto itt = bullets.begin();
	while (itt != bullets.end()) {
		if ((**itt).getLife() <= 0) itt = bullets.erase(itt);
		else if ((**itt).getPosition().y < 0 || (**itt).getPosition().y > window.getSize().y) itt = bullets.erase(itt);
		else ++itt;
	}
	bullets.shrink_to_fit();
}
