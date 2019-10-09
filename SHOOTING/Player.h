#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::Color fillColor)
	{
		instance = sf::CircleShape(20, 4);
		instance.setFillColor(fillColor);
		instance.setOrigin(instance.getRadius(), instance.getRadius());
	}
	void setPosMiddleOfXAndSetY(float width, float y)
	{
		instance.setPosition(width / 2, y);
	}
	void move(sf::Vector2f speed)
	{
		setPosition(instance.getPosition() + speed);
	}
	void setPosition(sf::Vector2f pos)
	{
		instance.setPosition(pos);
	}
	bool Hurt(int damage=1)
	{
		health -= damage;

		if (health < 0)
		{
			health = 0;
			isDie = true;

			return false;
		}

		return true;
	}

	bool IsDie()
	{
		return isDie;
	}

	int getHealth()
	{
		return health;
	}

	sf::FloatRect getGlobalBounds()
	{
		return instance.getGlobalBounds();
	}
	sf::Vector2f getPosition()
	{
		return instance.getPosition();
	}
	sf::CircleShape getInstance()
	{
		return instance;
	}

	const int MAX_HEALTH = 10;
private:
	int isDie = false;
	int health = MAX_HEALTH;
	sf::CircleShape instance;
};