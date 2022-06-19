#include "StatusBar.h"


StatusBar::StatusBar() {}
StatusBar::StatusBar(const std::string& lifeBarTexPath, const std::string& backgroundTexPath, const std::string& levelName, const sf::Font& font_, const int characterSize, const int life_) {
	life = life_;

	//setting parameters for lifebar
	lifeBarTex.loadFromFile(lifeBarTexPath);
	lifeBar.setTexture(lifeBarTex);
	lifeBar.setPosition(20, 20);
	lifeBar.setScale(3, 3);
	lifeBar.setPosition(0, 0);

	//setting parameters for background
	backgroundTex.loadFromFile(backgroundTexPath);
	background.setTexture(backgroundTex);

	//setting fonts for text
	font = font_;
	levelNameText.setFont(font);
	bonusNameText.setFont(font);
	enemyText.setFont(font);

	//setting character size for text
	levelNameText.setCharacterSize(characterSize);
	bonusNameText.setCharacterSize(characterSize);
	enemyText.setCharacterSize(characterSize);

	//setting position for objects
	enemyText.setPosition(360, 20);
	bonusNameText.setPosition(650, 20);
	levelNameText.setPosition(980, 20);

	activeLevelName = levelName;
}

//drawing function for level
void StatusBar::show(sf::RenderWindow& window) {
	setLifeRect();
	setValue();
	window.draw(background);
	window.draw(lifeBar);
	window.draw(enemyText);
	window.draw(bonusNameText);
	window.draw(levelNameText);
}
//setings value for texts
void StatusBar::setValue() {
	enemyText.setString("ENEMIES DEFETED\n" + std::to_string(enemyCounter));
	bonusNameText.setString("ACTIVE BONUS \n" + activeBonusName);
	levelNameText.setString("LEVEL NAME\n" + activeLevelName);
}
void StatusBar::addEnemies() { ++enemyCounter; }
void StatusBar::setLive(const int tmp) { life = tmp; }
void StatusBar::setLevelName(const std::string& tmp) { activeLevelName = tmp; }
void StatusBar::setBonus(const BulletType& type) {
	switch (type)
	{
	case BulletType::LINEAR:
		activeBonusName = "NORMAL BULLET";
		break;
	case BulletType::SLOW_LINEAR:
		activeBonusName = "SLOW BULLET";
		break;
	case BulletType::FAST_LINEAR:
		activeBonusName = "FAST BULLET";
		break;
	}
}

//life bar service
void StatusBar::setLifeRect() {
	lifeBar.setTextureRect(sf::IntRect(18, 22, 25 * life, 10));
}