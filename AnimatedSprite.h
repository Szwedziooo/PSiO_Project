#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class AnimatedSprite : public sf::Sprite
{
private:
	sf::Vector2f startPosition;
	sf::Texture texture;
	bool isControllable;
	bool isPasive;
	bool isBonus;
	int life = 0;
public:
	AnimatedSprite();
	AnimatedSprite(const string &path,const sf::Vector2f &startPos, const bool isControllable_, const bool isPasive_) {
		isBonus = 0;
		isControllable = isControllable_;
		isPasive = isPasive_;
		texture.loadFromFile(path);
		this->setTexture(texture);
		startPosition = startPos;
		setPosition(startPosition);
	}

	//abstract animation function
	virtual void animation(sf::Time& time) = 0;

	//returns specific values
	sf::Vector2f getStartPosition();
	virtual bool getControllable();
	virtual int getLife();
	virtual bool getPasive();
	virtual bool getIsBonus();
	
	//sets specific values
	virtual void setIsBonus(const bool);
	virtual void setLife(int);
	void setStartPosition(sf::Vector2f&);
	
	bool colision(AnimatedSprite&s);
	

};