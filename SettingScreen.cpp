#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "GameScreen.h"
#include "SettingScreen.h"
#include "MenuScreen.h"
#include "Snake.h"
#include "Game.h"
using namespace sfSnake;


//整个继承类SettingScreen的实现
SettingScreen::SettingScreen()
{
    font_.loadFromFile("Fonts/game_over.ttf");
    setText();
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void SettingScreen::handleInput(sf::RenderWindow &window)//键盘控制的实现，修改GameScreen的几个全局变量
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        Game::Screen = std::make_shared<MenuScreen>();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && GameScreen::fruitNum < 30)
    {
        GameScreen::fruitNum++;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && GameScreen::fruitNum > 1)
    {
        GameScreen::fruitNum--;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Snake::InitialSize < 20)
    {
        Snake::InitialSize++;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Snake::InitialSize > 5)
    {
        Snake::InitialSize--;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
    {
        GameScreen::haveLines = true;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
    {
        GameScreen::haveLines = false;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        GameScreen::backgroundStyle = 1;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        GameScreen::backgroundStyle = 2;
        setText();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        GameScreen::backgroundStyle = 3;
        setText();
    }
}

void SettingScreen::update(sf::Time delta)
{
}

void SettingScreen::render(sf::RenderWindow &window)
{
    window.draw(text_);
}

void SettingScreen::setText()
{
    text_.setFont(font_);
    text_.setString(
        "\n\n[UP/DOWN] Fruits:" +
        std::to_string(GameScreen::fruitNum) +
        "\n\n[LEFT/RIGHT] Length:" + std::to_string(Snake::InitialSize) +
        "\n\n[Y/N] Havelines:" + (GameScreen::haveLines ? "Yes" : "No") +
        "\n\n[1/2/3] Background:" + std::to_string(GameScreen::backgroundStyle) +
        "\n\n[ESC] Back To Menu");
}