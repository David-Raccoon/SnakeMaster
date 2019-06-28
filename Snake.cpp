#include <SFML/Graphics.hpp>

#include <memory>
#include <cmath>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;
using namespace std;

int Snake::InitialSize = 10;

Snake::Snake() : hitSelf_(false), direction_(0.f, -1.f)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);

	switch (GameScreen::backgroundStyle)//蛇头纹理的选择，由背景颜色而定
	{
	case 1:
		headImage_.loadFromFile("Pictures/snakehead1.png");
		break;
	case 2:
		headImage_.loadFromFile("Pictures/snakehead2.png");
		break;
	case 3:
		headImage_.loadFromFile("Pictures/snakehead3.png");
		break;
	}
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		float x = Game::Width / 2 - SnakeNode::Width / 2;
		float y = Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i);
		nodes_.push_back(SnakeNode(sf::Vector2f(x, y), direction_, i));
	}
}

void Snake::handleInput(sf::RenderWindow &window)
{
	sf::Vector2f newDirection(direction_);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//鼠标控制方向的实现
	{
		sf::Vector2i mousePosition(sf::Mouse::getPosition(window));
		sf::Vector2f headPosition(getPosition());
		sf::Vector2f direction(mousePosition.x - headPosition.x, mousePosition.y - headPosition.y);
		float x = direction.x / sqrt(direction.x * direction.x + direction.y * direction.y);
		float y = direction.y / sqrt(direction.x * direction.x + direction.y * direction.y);
		newDirection = sf::Vector2f(x, y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//键盘控制方向的实现
		newDirection = sf::Vector2f(0.f, -1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		newDirection = sf::Vector2f(0.f, 1.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		newDirection = sf::Vector2f(-1.f, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		newDirection = sf::Vector2f(1.f, 0.f);

	if (newDirection.x * direction_.x + newDirection.y * direction_.y < -sqrt(3) / 2)
		return; //大于150度不转向

	direction_ = newDirection;
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit> &fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		int growTimes;
		switch (toRemove->getColor())
		{
		case FruitColor::Brown:
		case FruitColor::Black:
			growTimes = 0;
			break;
		case FruitColor::Blue:
			growTimes = 1;
			break;
		case FruitColor::Green:
			growTimes = 2;
			break;
		case FruitColor::Red:
			growTimes = 3;
			break;
		}
		grow(growTimes);
		fruits.erase(toRemove);
	}
}

void Snake::grow(int growTimes)//根据水果颜色确定生长长度
{
	int i = 0;
	while (i++ < growTimes)
	{
		float x = nodes_[nodes_.size() - 1].getPosition().x - nodes_[nodes_.size() - 1].getDirection().x * SnakeNode::Height;
		float y = nodes_[nodes_.size() - 1].getPosition().y - nodes_[nodes_.size() - 1].getDirection().y * SnakeNode::Height;
		nodes_.push_back(SnakeNode(sf::Vector2f(x, y), nodes_[nodes_.size() - 1].getDirection(), (int)nodes_.size()));
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

sf::Vector2f Snake::getPosition() const
{
	return nodes_[0].getPosition();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode &headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)//优化了一下死亡判定函数
	{
		float deltaX = headNode.getPosition().x - nodes_[i].getPosition().x;
		float deltaY = headNode.getPosition().y - nodes_[i].getPosition().y;
		if (sqrt(deltaX * deltaX + deltaY * deltaY) < SnakeNode::Height / 2)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode &headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()//鼠标控制下的move函数实现
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].setDirection(nodes_.at(i - 1).getDirection());
	}
	sf::Vector2f prevDirection = nodes_[0].getDirection();
	if (prevDirection.x * direction_.y - prevDirection.y * direction_.x > 0) //右旋
	{
		nodes_[0].move(-SnakeNode::Width * prevDirection.y, SnakeNode::Width * prevDirection.x);
		nodes_[0].setDirection(direction_);
		nodes_[0].move(SnakeNode::Width * direction_.y, -SnakeNode::Width * direction_.x);
		nodes_[0].move(SnakeNode::Height * direction_.x, SnakeNode::Height * direction_.y);
	}
	else
	{
		nodes_[0].setDirection(direction_);
		nodes_[0].move(SnakeNode::Height * direction_.x, SnakeNode::Height * direction_.y);
	}
}

void Snake::render(sf::RenderWindow &window)
{
	for (decltype(nodes_.size()) i = 0; i < nodes_.size(); ++i)
	{
		if (i == 0) //绘制蛇头
		{
			sf::RectangleShape snakeHead(sf::Vector2f(SnakeNode::Width, 2 * SnakeNode::Height));
			sf::Vector2f headPosition;
			headPosition.x = nodes_[i].getPosition().x + nodes_[i].getDirection().x * SnakeNode::Height;
			headPosition.y = nodes_[i].getPosition().y + nodes_[i].getDirection().y * SnakeNode::Height;
			snakeHead.setPosition(headPosition);
			snakeHead.setRotation(nodes_[i].getRotation());
			snakeHead.setTexture(&headImage_);
			window.draw(snakeHead);
			continue;
		}

		if (i != 0 && nodes_[i].getDirection() != nodes_[i - 1].getDirection()) //绘制转折点
		{
			sf::ConvexShape turning;
			turning.setPointCount(3);
			sf::Vector2f point0, point1, point2;

			point0 = nodes_[i].getPosition();

			point1.x = point0.x - SnakeNode::Width * nodes_[i].getDirection().y;
			point1.y = point0.y + SnakeNode::Width * nodes_[i].getDirection().x;

			if (nodes_[i].getDirection().x * nodes_[i - 1].getDirection().y - nodes_[i].getDirection().y * nodes_[i - 1].getDirection().x > 0) //右旋
			{
				point2.x = point1.x + SnakeNode::Width * nodes_[i - 1].getDirection().y;
				point2.y = point1.y - SnakeNode::Width * nodes_[i - 1].getDirection().x;
			}

			else
			{
				point2.x = point0.x - SnakeNode::Width * nodes_[i - 1].getDirection().y;
				point2.y = point0.y + SnakeNode::Width * nodes_[i - 1].getDirection().x;
			}

			turning.setPoint(0, point0);
			turning.setPoint(1, point1);
			turning.setPoint(2, point2);

			turning.setFillColor(i % 2 ? sf::Color::Red : sf::Color::Yellow);
			turning.setOutlineColor(sf::Color::White);
			turning.setOutlineThickness(0.f);
			window.draw(turning);
		}

		nodes_[i].render(window);//常规绘制
	}
}