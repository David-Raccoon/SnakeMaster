#include <SFML/Graphics.hpp>
#include <cmath>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position, sf::Vector2f direction, int sequence)
	: position_(position), direction_(direction), sequence_(sequence)
{
	shape_.setPosition(position_);

	float rotation_;
	if (direction_.x == 0)
		rotation_ = (direction_.y > 0) ? 180 : 0;
	else
		rotation_ = atan(direction_.y / direction_.x) * 180 / M_PI + +((direction_.x > 0) ? 90 : 270);
	shape_.setRotation(rotation_);

	shape_.setFillColor(sequence_ % 2 ? sf::Color::Red : sf::Color::Yellow);
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(0.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::setDirection(sf::Vector2f direction)
{
	direction_ = direction;
	float rotation_;
	if (direction_.x == 0)
		rotation_ = (direction_.y > 0) ? 180 : 0;
	else
		rotation_ = atan(direction_.y / direction_.x) * 180 / M_PI + ((direction_.x > 0) ? 90 : 270);
	shape_.setRotation(rotation_);
}

void SnakeNode::setDirection(float x, float y)
{
	direction_ = sf::Vector2f(x, y);
	float rotation_;
	if (direction_.x == 0)
		rotation_ = (direction_.y > 0) ? 180 : 0;
	else
		rotation_ = atan(direction_.y / direction_.x) * 180 / M_PI + ((direction_.x > 0) ? 90 : 270);
	shape_.setRotation(rotation_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

sf::Vector2f SnakeNode::getDirection() const
{
	return direction_;
}

float SnakeNode::getRotation() const
{
	return shape_.getRotation();
}

void SnakeNode::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}