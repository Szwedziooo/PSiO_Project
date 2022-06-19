#include "Bonus.h"

Bonus::Bonus(){}

void Bonus::animation(sf::Time& time) {
	startFrame(time);
	move(0, speed * time.asSeconds());
}

void Bonus::generate() {
	switch (rand() % 10)
	{
	case 0:
		bonus = BulletType::LINEAR;
		break;
	case 1:
		bonus = BulletType::FAST_LINEAR;
		break;
	case 2:
		bonus = BulletType::SLOW_LINEAR;
		break;
	default:
		generate();
		break;
	}
}

void Bonus::startFrame(sf::Time& time) {
	if (time_counter > 1) {
		++frame;
		if (frame == 3) frame = 0;
		setTextureRect(frames[frame]);
		time_counter = 0;
	}
	else time_counter += time.asSeconds();
}

BulletType Bonus::getBulletType() { return bonus; }