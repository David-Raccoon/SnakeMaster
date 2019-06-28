#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow &window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow &window) override;

	void generateFruit();

	static int fruitNum; //同时出现的水果数量
	static bool haveLines;
	static int backgroundStyle;

private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	std::vector<sf::RectangleShape> background_;
};
} // namespace sfSnake

#endif