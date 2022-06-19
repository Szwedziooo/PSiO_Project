#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

#include "AnimatedSprite.h"
#include "Button.h"
#include "Scene.h"
#include "Spaceship.h"
#include "Barricade.h"
#include "Bullet.h"
#include "Level.h"
#include "StatusBar.h"
#include "Bonus.h"

using namespace std;

class GameEngine
{
private:
	//Fundamental variables
	sf::RenderWindow window;
	sf::Time elapsed;
	sf::Clock clock;
	sf::Event event;
	sf::Cursor cursor;
	sf::Font font;
	sf::Text gameTitle;

	//Scene variable
	scene activeScene = scene::MENU;

	//Containers
	vector<unique_ptr<AnimatedSprite>> obj;
	vector<Button<scene>> buttons;
	vector<Button<SkinType>> skins_buttons;
	vector<unique_ptr<Bullet>> bullets;
	Spaceship *player;

	//Levels
	string levels_path = "levels/info.txt";
	vector <Button<string>> levels_buttons;
	string activeLevel;
	Level level;
	StatusBar *bar;

	//Game Over
	sf::Text gameOverText;

	//Bonus
	float time_counter = 0;

public:
	GameEngine() : window(sf::VideoMode(1240, 800), L"Space Ivanders") {
		//Window Setting 
		window.setFramerateLimit(120);
		window.setMouseCursorVisible(1);

		//Font 
		font.loadFromFile("fonts/space_invaders.ttf");

		//Game Title
		gameTitle.setString("Space\nInvaders");
		gameTitle.setPosition(300,100);
		gameTitle.setCharacterSize(70);
		gameTitle.setFont(font);

		//Player
		player = new Spaceship("images/spaceship.png", sf::Vector2f(0,0), true,SkinType::HERO_1,window.getSize());

		//Level
		loading_level_first_stage();
		cout << "Wczytane Poziomy: " << levels_buttons.size() << endl;

		//Game Over
		gameOverText.setString("GAME OVER");
		gameOverText.setFont(font);
		gameOverText.setCharacterSize(50);
		gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 4);
	}

	//main function
	void loop();

	//display sprites and buttons 
	void draw(sf::Time& );
	
	//changing active scene
	void scene_select(sf::Time& );

	//sets outline on button-text
	void hover();

	//select specific buttons to diffrent scenes
	void select_buttons();

	//play scene function
	void play(sf::Time& );

	//menu scene function
	void menu(sf::Time& );

	//skins scene function
	void skins(sf::Time& );

	//level picking scene function
	void levels(sf::Time&);

	//end of the game function
	void game_over();

	//first stage of loading levels from file
	void loading_level_first_stage();
	 
	//second stage of loading levels from file
	void loading_level_second_stage();

	//generate bonus objects
	void generateBonus(sf::Time&);
	
	void collision_management(AnimatedSprite&, AnimatedSprite&);

	void removeObj();
};