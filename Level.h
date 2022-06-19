#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "AnimatedSprite.h"
#include "Spaceship.h"
#include "Barricade.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "StatusBar.h"

class Level
{
public:
	Level();
	Level(const std::string&, const sf::Font&, const int, const int);

	std::vector < std::unique_ptr<AnimatedSprite>> load_level(const sf::Vector2u&);
	SkinType convert_skin(const std::string&);
	BarricadeType conver_barricade(const std::string& );
	std::string getLevelName();
	StatusBar* getStatusBar();
private:
	std::string level_name;
	std::string level_path;
	StatusBar *bar;
};

