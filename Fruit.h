#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{

enum class FruitColor
{
	Red,   //grow(3)
	Green, //grow(2)
	Blue,  //grow(1)
	Black, //grow(0)
	Brown  //grow(0)
};

class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), FruitColor fruitColor = FruitColor::Red);

	void render(sf::RenderWindow &window);

	sf::FloatRect getBounds() const;
	FruitColor getColor() const;

private:
	sf::CircleShape shape_;
	FruitColor fruitColor_;
	static const float Radius;
};
} // namespace sfSnake

#endif