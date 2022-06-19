#pragma once
#include "AnimatedSprite.h"
#include "Bullet.h"

enum class SkinType {
	ENEMY_BLUE,
	ENEMY_RED,
	ENEMY_WHITE,
	HERO_1,
	HERO_2,
	HERO_3,
	BARRICADE
};

class Spaceship : public AnimatedSprite
{
public:
	Spaceship();
	Spaceship(const std::string& path, const sf::Vector2f& startPos, const bool isControllable_,const SkinType &type_,const sf::Vector2u &window_size_) : AnimatedSprite(path, startPos,isControllable_,0) {
		this->type = type_;
		this->window_size = window_size_;
		this->bulletType = BulletType::LINEAR;

		setLife(4);

		skinSelect(type);
		if (getControllable()) {
			setScale(2.5, 2.5);
			sf::Vector2f tmp = { window_size.x / 2 - getGlobalBounds().width / 2,700 };
			setStartPosition(tmp);
			setPosition(tmp);
		}
		else setScale(2.5, -2.5);
	}
	//Main animation function for Spaceship
	void animation(sf::Time&);
	
	//Set spaceship to default position
	virtual void setObjToDefaultPosition();
	
	//Create bullets 
	void shoot(std::vector<std::unique_ptr<Bullet>>&);

	//Select skin and other basic properties
	void skinSelect(SkinType&);

	//Switch stages of enamies
	void switchPhase();

	//Control of avatar
	void control(sf::Time& );

	//Function detect borders of window
	void borderDetection();

	//Function set skin
	void setSkin(const SkinType&);

	//Function set enum BulletType
	void setBulletType(BulletType&);

	//Return enum BulletType
	BulletType getBulletType();

private:
	sf::Vector2i direction;
	sf::Vector2u window_size;
	float speed = 0;
	SkinType type;
	BulletType bulletType;
	float time_counter = 0;
	float mulitiplier = 1.0;
};