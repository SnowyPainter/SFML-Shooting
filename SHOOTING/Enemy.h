#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(sf::Color fillColor)
	{
		instance = sf::CircleShape(35, 3);
		instance.setFillColor(fillColor);
		instance.setOrigin(instance.getRadius(), instance.getRadius());
	}
	bool moveDownfall(float speed, int windowHeight)
	{
		instance.setPosition(instance.getPosition() + sf::Vector2f{0, isDead ? 3:speed});

		if (instance.getPosition().y > windowHeight)
			return false;

		return true;
	}
	void setPosition(float x, float y)
	{
		instance.setPosition(x, y);
	}
	void setDead(sf::Color deadColor=sf::Color::Red)
	{
		isDead = true;
		instance.setFillColor(deadColor);
	}
	bool isDie()
	{
		return isDead;
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
	bool isDead = false;
	sf::CircleShape instance;
};