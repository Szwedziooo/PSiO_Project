#include "Level.h"

Level:: Level() {}
Level::Level(const std::string& path, const sf::Font& font, const int characterSize, const int life) :level_path(path) {
	bar = new StatusBar("images/lifebar.png", "images/statusbar.png", level_name, font, characterSize, life);
}

//Return loaded vector of objects
std::vector < std::unique_ptr<AnimatedSprite>> Level::load_level(const sf::Vector2u& window_size) {
	ifstream file(level_path);
	std::vector < std::unique_ptr<AnimatedSprite>> tmp;
	std::string data[6];

	if (file.is_open()) {
		file >> level_name;
		cout << level_name << endl;
		bar->setLevelName(level_name);
		while (!file.eof()) {
			file >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5];
			if (data[1] == "spaceship")
				tmp.emplace_back(std::make_unique<Spaceship>(data[0], sf::Vector2f(std::stoi(data[2]), std::stoi(data[3])), std::stoi(data[4]), convert_skin(data[5]), window_size));
			else if (data[1] == "barricade")
				tmp.emplace_back(std::make_unique<Barricade>(data[0], sf::Vector2f(std::stoi(data[2]), std::stoi(data[3])), std::stoi(data[4]), conver_barricade(data[5])));
			data[1] = "";
		}
		file.close();
		return tmp;
	}
	else return std::vector<std::unique_ptr<AnimatedSprite>>();
}

//Convert string to enum SkinType
SkinType Level::convert_skin(const std::string& tmp) {
	if (tmp == "ENEMY_WHITE") return SkinType::ENEMY_WHITE;
	else if (tmp == "ENEMY_BLUE") return SkinType::ENEMY_BLUE;
	else if (tmp == "ENEMY_RED") return SkinType::ENEMY_RED;
	else if (tmp == "BARRICADE") return SkinType::BARRICADE;
}

//Convert string to enum BarricadeType
BarricadeType Level::conver_barricade(const std::string& tmp) {
	if (tmp == "FIRST_STAGE") return BarricadeType::FIRST_STAGE;
	else if (tmp == "SECOND_STAGE") return BarricadeType::SECOND_STAGE;
	else if (tmp == "THIRD_STAGE") return BarricadeType::THIRD_STAGE;
	else if (tmp == "LAST_STAGE") return BarricadeType::LAST_STAGE;
}

//Return level name
std::string Level::getLevelName() { return level_name; }

//Return StatusBar
StatusBar* Level::getStatusBar() { return bar; }