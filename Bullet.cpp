#include "Bullet.h"

Bullet::Bullet(){}

void Bullet::animation(sf::Time& time) {
	move(0, speed * time.asSeconds() * bullet_dir);
}

bool Bullet::outOfBounds(const sf::Vector2u& window_size) {
	return (this->getPosition().y < 0 || this->getGlobalBounds().top > window_size.y);
}

int Bullet::getBulletDir() { return bullet_dir; }

void Bullet::setSpeed() {
	switch (type)
	{
	case BulletType::LINEAR:
		setTextureRect(sf::IntRect(362, 9, 13, 23));
		speed = 200;
		break;
	case BulletType::SLOW_LINEAR:
		setTextureRect(sf::IntRect(413, 9, 13, 23));
		speed = 100;
		break;
	case BulletType::FAST_LINEAR:
		setTextureRect(sf::IntRect(379, 9, 13, 23));
		speed = 300;
		break;
	}
}