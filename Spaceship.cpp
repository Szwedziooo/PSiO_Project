#include "Spaceship.h"

Spaceship::Spaceship() {}

//Main animation function for Spaceship
void Spaceship::animation(sf::Time& time) {
	control(time);
	switchPhase();
}

void Spaceship::setObjToDefaultPosition() {
	setPosition(getStartPosition());
}

void Spaceship::shoot(std::vector<std::unique_ptr<Bullet>>& vec) {
	if (getControllable()) {
		vec.emplace_back(std::make_unique<Bullet>("images/bullet.png", sf::Vector2f(getPosition().x - 7 + getGlobalBounds().width/2, getPosition().y), bulletType, 1));
	}
	else {
		if (rand() % 600 < 1)
			vec.emplace_back(std::make_unique<Bullet>("images/bullet.png", sf::Vector2f(getPosition().x - 7 + getGlobalBounds().width / 2, getPosition().y), bulletType, 0));
	}
}

void Spaceship::skinSelect(SkinType& type_) {
	switch (type_)
	{
	case SkinType::ENEMY_BLUE:
		cout << getControllable() << endl;
		this->setTextureRect(sf::IntRect(162, 2, 28, 28));
		this->bulletType = BulletType::FAST_LINEAR;
		this->setLife(5);
		speed = 100;
		break;
	case SkinType::ENEMY_RED:
		this->setTextureRect(sf::IntRect(354, 2, 28, 28));
		this->bulletType = BulletType::LINEAR;
		this->setLife(5);
		speed = 150;
		break;
	case SkinType::ENEMY_WHITE:
		this->setTextureRect(sf::IntRect(546, 2, 28, 28));
		this->bulletType = BulletType::SLOW_LINEAR;
		this->setLife(2);
		speed = 100;
		break;
	case SkinType::HERO_1:
		this->setTextureRect(sf::IntRect(1, 257, 30, 30));
		speed = 200;
		break;
	case SkinType::HERO_2:
		this->setTextureRect(sf::IntRect(65, 290, 30, 30));
		speed = 200;
		break;
	case SkinType::HERO_3:
		this->setTextureRect(sf::IntRect(33, 257, 30, 30));
		speed = 200;
		break;
	}
}

void Spaceship::switchPhase() {
	if (type != SkinType::HERO_1 && type != SkinType::HERO_2 && type != SkinType::HERO_3)
		if (getLife() < 4) mulitiplier = 1.1;
		else if (getLife() < 3) mulitiplier = 1.2;
		else if (getLife() < 2) mulitiplier = 1.4;
}

void Spaceship::control(sf::Time& time) {
	direction = { 0,0 };
	if (getControllable()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))direction.y = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))direction.y = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))direction.x = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))direction.x = -1;
		move(direction.x * speed * time.asSeconds(), direction.y * speed * time.asSeconds());
	}
	else {
		switch (type)
		{
		case SkinType::ENEMY_BLUE:
			move(speed * time.asSeconds() * mulitiplier, 0);
			break;
		case SkinType::ENEMY_RED:
			move(-speed * time.asSeconds() * mulitiplier, 0);
			break;
		case SkinType::ENEMY_WHITE:
			if (time_counter < 4) move(0, speed * time.asSeconds() * mulitiplier);
			else if (time_counter < 8)move(0, -(speed)*time.asSeconds() * mulitiplier);
			else time_counter = 0;
			time_counter += time.asSeconds();
			break;
		case SkinType::BARRICADE:
			break;
		}
	}
	borderDetection();
}

void Spaceship::borderDetection() {
	if (getGlobalBounds().left < 0) setPosition(window_size.x - getGlobalBounds().width, getPosition().y);
	else if (getGlobalBounds().left + getGlobalBounds().width > window_size.x) setPosition(0, getPosition().y);
}
void Spaceship::setSkin(const SkinType& tmp) {
	type = tmp;
	skinSelect(type);
}
void Spaceship::setBulletType(BulletType& tmp) { bulletType = tmp; }
BulletType Spaceship::getBulletType() { return bulletType; }
