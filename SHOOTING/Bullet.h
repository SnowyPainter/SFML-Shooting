#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
public:
	Bullet(float speed)
	{
		this->speed = sf::Vector2f(0, -speed);

		instance = sf::CircleShape(10, 8);
		instance.setFillColor(sf::Color::Green);
		instance.setOrigin(instance.getRadius(), instance.getRadius());
	}
	void ShootInit(sf::Vector2f startPos)
	{
		startPosition = startPos;
		instance.setPosition(startPosition);
		init = true;
	}
	sf::Vector2f getPos()
	{
		return instance.getPosition();
	}
	bool ShootForward()
	{

		if (init && instance.getPosition().y > 0)
		{
			instance.setPosition(instance.getPosition() + speed);
			return true;
		}
		else
			return false;

	}
	void stop()
	{
		init = false;
	}
	sf::FloatRect getGlobalBounds()
	{
		return instance.getGlobalBounds();
	}
	sf::CircleShape getInstance()
	{
		return instance;
	}
private:
	int init = false;

	sf::Vector2f speed, startPosition;
	sf::CircleShape instance;
};