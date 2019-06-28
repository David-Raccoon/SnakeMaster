#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

int GameScreen::fruitNum = 15;
bool GameScreen::haveLines = true;
int GameScreen::backgroundStyle = 1;//改为全局变量以便设置

GameScreen::GameScreen() : snake_()
{
	//底色的实现
	sf::RectangleShape ground(sf::Vector2f(Game::Width, Game::Height));
	ground.setPosition(0.f, 0.f);
	switch (backgroundStyle)
	{
	case 1:
		ground.setFillColor(sf::Color::White);
		break;
	case 2:
		ground.setFillColor(sf::Color(220, 220, 220));
		break;
	case 3:
		ground.setFillColor(sf::Color::Black);
		break;
	}
	background_.push_back(ground);

	//网格的实现
	if (haveLines)
	{
		sf::RectangleShape row(sf::Vector2f(Game::Width, 1.f));
		for (float y = 0.f; y < Game::Height; y += SnakeNode::Height)
		{
			row.setPosition(0.f, y);
			row.setFillColor(sf::Color(192, 192, 192)); //灰色
			background_.push_back(row);
		}

		sf::RectangleShape column(sf::Vector2f(1.f, Game::Height));
		for (float x = 0.f; x < Game::Width; x += SnakeNode::Height)
		{
			column.setPosition(x, 0.f);
			column.setFillColor(sf::Color(192, 192, 192)); //灰色
			background_.push_back(column);
		}
	}
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	while (fruit_.size() < fruitNum)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow &window)
{
	for (auto line : background_) //背景绘制
		window.draw(line);

	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
	static std::uniform_int_distribution<int> typeDistribution(1, 100);

	int type = typeDistribution(engine);
	FruitColor color;
	if (type >= 1 && type <= 12)
		color = FruitColor::Brown;
	if (type >= 13 && type <= 25)
		color = FruitColor::Black;
	if (type >= 26 && type <= 50)
		color = FruitColor::Blue;
	if (type >= 51 && type <= 75)
		color = FruitColor::Green;
	if (type >= 76 && type <= 100)
		color = FruitColor::Red;

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), color));
}
