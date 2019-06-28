#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f direction = sf::Vector2f(0.f, -1.f), int sequence = 0);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setDirection(sf::Vector2f position);
	void setDirection(float x, float y);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow &window);

	sf::Vector2f getPosition() const;
	sf::Vector2f getDirection() const;
	float getRotation() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const float Height;

private:
	sf::RectangleShape shape_;
	sf::Vector2f position_;
	sf::Vector2f direction_;
	int sequence_;
};
} // namespace sfSnake

#endif