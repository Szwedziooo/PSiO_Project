#pragma once
#include "AnimatedSprite.h"
#include "Spaceship.h"

class Bonus : public AnimatedSprite
{
private:
	float speed;
	BulletType bonus;
	float time_counter = 0;
	std::vector<sf::IntRect> frames;
	int frame = 1;
public:
	Bonus();
	Bonus(const std::string& path, const sf::Vector2f& pos, const bool isControllable_) : AnimatedSprite(path, pos, isControllable_, 0) {
		setLife(1);
		generate();
		speed = 100;
		setIsBonus(1);

		//setting scale for Bonus texture
		setScale(4, 4);

		//setting animation frames
		frames.emplace_back(sf::IntRect(1, 1, 13, 14));
		frames.emplace_back(sf::IntRect(76, 17, 13, 14));
		frames.emplace_back(sf::IntRect(106, 1, 13, 14));
		setTextureRect(frames[0]);
	}
	//Main animation function for Bonus
	void animation(sf::Time&);
	//Random generate Bonus properties
	void generate();
	//Frame animation service
	void startFrame(sf::Time&);
	//Return Bonus value (BulletType)
	BulletType getBulletType();
};

