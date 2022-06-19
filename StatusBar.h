#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"

class StatusBar
{
public:
	StatusBar();
	StatusBar(const std::string&, const std::string&, const std::string&, const sf::Font&, const int, const int);

	//drawing function for level
	void show(sf::RenderWindow&);

	//setings value for texts
	void setValue();
	void addEnemies();
	void setLive(const int);
	void setLevelName(const std::string&);
	void setBonus(const BulletType&);

	//life bar service
	void setLifeRect();

private:
	//Life Bar
	sf::Sprite lifeBar;
	sf::Texture lifeBarTex;
	int life = 4;
	
	//Background
	sf::Sprite background;
	sf::Texture backgroundTex;
	
	//Font
	sf::Font font;

	//Level Name
	std::string activeLevelName;
	sf::Text levelNameText;
	
	//Bonus Name
	std::string activeBonusName = "LINEAR SHOOTING";
	sf::Text bonusNameText;

	//Defeated Enemies Counter
	sf::Text enemyText;
	int enemyCounter = 0;

};

