#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(){}

void AnimatedSprite::animation(sf::Time& time) {}

sf::Vector2f AnimatedSprite::getStartPosition() { return startPosition; }

bool AnimatedSprite::getControllable() { return isControllable; }
int AnimatedSprite::getLife() { return life; }
bool AnimatedSprite::getPasive() { return isPasive; }
bool AnimatedSprite::getIsBonus() { return isBonus; }

void AnimatedSprite::setIsBonus(const bool tmp) { isBonus = tmp; }
void AnimatedSprite::setLife(int life_) { life = life_; }
void AnimatedSprite::setStartPosition(sf::Vector2f& pos) { startPosition = pos; }

bool AnimatedSprite::colision(AnimatedSprite& obj) {
	return this->getGlobalBounds().intersects(obj.getGlobalBounds());
}