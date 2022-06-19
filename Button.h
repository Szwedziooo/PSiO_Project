#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Scene.h"
#include <iostream>

template <class T>
class Button :public sf::Text
{
private:
	T value;
public:
	Button <T> () = default;
	Button <T> (const std::string &text,const sf::Font &font,const int &size,const sf::Vector2f &position,const T &tmp) : sf::Text(text,font,size) {
		setPosition(position);
		value = tmp;
		setOutlineColor(sf::Color::Cyan);
	}
	T executre() {
		return value;
	}
	void hover(sf::Vector2i mouse){
		if (getGlobalBounds().contains(mouse.x, mouse.y)) {
			setOutlineThickness(5);
		}
		else setOutlineThickness(0);
	}
	bool mouse_click(sf::Vector2i mouse) {
		return getGlobalBounds().contains(mouse.x, mouse.y);
	}
};


