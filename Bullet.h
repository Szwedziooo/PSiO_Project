#pragma once
#include "AnimatedSprite.h"
#include "Barricade.h"

enum class BulletType {
	LINEAR,
	SLOW_LINEAR,
	FAST_LINEAR
};

class Bullet : public AnimatedSprite
{
	BulletType type;
	int bullet_dir;
	float speed;
public:
	Bullet();
	Bullet(const std::string& path, const sf::Vector2f& pos, const BulletType& type_, const bool isControllable_): AnimatedSprite(path,pos,isControllable_,0) {
		this->type = type_;
		setLife(1);
		
		if (getControllable()) {
			bullet_dir = -1;
		}
		else bullet_dir = 1;

		setSpeed();
	}

	void animation(sf::Time&);

	bool outOfBounds(const sf::Vector2u&);

	int getBulletDir();

	void setSpeed();

};

