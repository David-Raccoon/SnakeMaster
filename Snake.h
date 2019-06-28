#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow &window);
	void update(sf::Time delta);
	void render(sf::RenderWindow &window);

	void checkFruitCollisions(std::vector<Fruit> &fruits);

	bool hitSelf() const;

	unsigned getSize() const;
	sf::Vector2f getPosition() const; //得到蛇头的位置
	sf::Vector2f getDirection() const;
	static int InitialSize;

private:
	void move();
	void grow(int growTimes = 1); //add parameters growTimes(default 1)
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;

	sf::Texture headImage_;
};
} // namespace sfSnake

#endif