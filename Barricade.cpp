#include "Barricade.h"

void Barricade::animation(sf::Time& time) {
	lifeCheck();
}

void Barricade::lifeCheck() {
	if (getLife() == 3) type = BarricadeType::SECOND_STAGE;
	else if (getLife() == 2) type = BarricadeType::THIRD_STAGE;
	else if (getLife() == 1) type = BarricadeType::LAST_STAGE;
	changeType();
}

void Barricade::changeType() {
	switch (type)
	{
	case BarricadeType::FIRST_STAGE:
		setTextureRect(sf::IntRect(5, 147, 105, 94));
		break;
	case BarricadeType::SECOND_STAGE:
		setTextureRect(sf::IntRect(9, 261, 102, 98));
		setLife(3);

		break;
	case BarricadeType::THIRD_STAGE:
		setTextureRect(sf::IntRect(10, 381, 102, 92));
		setLife(2);

		break;
	case BarricadeType::LAST_STAGE:
		setTextureRect(sf::IntRect(17, 28, 90, 83));
		setLife(1);
		break;
	}
}