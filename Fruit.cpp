#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 10.f;

Fruit::Fruit(sf::Vector2f position, FruitColor fruitColor)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	fruitColor_ = fruitColor;
	switch (fruitColor_)			//增加了水果颜色的实现
	{
	case FruitColor::Red:
		shape_.setFillColor(sf::Color::Red);
		break;
	case FruitColor::Green:
		shape_.setFillColor(sf::Color::Green);
		break;
	case FruitColor::Blue:
		shape_.setFillColor(sf::Color::Blue);
		break;
	case FruitColor::Black:
		shape_.setFillColor(sf::Color::Black);
		break;
	case FruitColor::Brown:
		shape_.setFillColor(sf::Color(128, 42, 42));
		break;
	}
}

void Fruit::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

sfSnake::FruitColor Fruit::getColor() const
{
	return fruitColor_;
}