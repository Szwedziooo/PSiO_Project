#include <iostream>
#include "GameEngine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ctime"

int main() {
	srand(time(NULL));
	GameEngine engine;
	engine.loop();
	return 0;
}