#pragma once
#include "AnimatedSprite.h"
#include <iostream>

enum class BarricadeType {
	FIRST_STAGE,
	SECOND_STAGE,
	THIRD_STAGE,
	LAST_STAGE
};

class Barricade : public AnimatedSprite
{
	BarricadeType type;
public:
	Barricade() {}
	Barricade(const std::string& path, const sf::Vector2f& startPos, const bool isControllable_, const BarricadeType& type_ = BarricadeType::FIRST_STAGE) : AnimatedSprite(path, startPos, isControllable_, 1) {
		type = type_;
		setLife(7);
		changeType();
	}

	void animation(sf::Time& time);

	void lifeCheck();
	void changeType();

};