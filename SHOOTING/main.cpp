#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

const int width = 768, height = 800;

int main()
{
	RenderWindow app(VideoMode(width, height), "The Rhombus");
	app.setFramerateLimit(60);
	//----Declare/Define Game Objects
	//-------------------
	vector<Bullet> bullets;
	vector<Enemy> enemies;
	Player player(Color::White);
	
	Font mainFont; 
	Text gameDoneMsg = Text("",mainFont);
	Text scoreText = Text("SCORE/0", mainFont);
	Text healthText = Text("HEALTH/MAX", mainFont);
	//-------------------
	
	//----GameObject Settings
	player.setPosMiddleOfXAndSetY(width, height - 100);

	if (!mainFont.loadFromFile("./Assets/font.ttf")) return -1;
	scoreText.setFillColor(Color::Black);
	healthText.setFillColor(Color::Black);
	gameDoneMsg.setFillColor(Color::Red);

	scoreText.setPosition(width / 2-scoreText.getLocalBounds().width/2, 0);
	healthText.setPosition(width / 2-healthText.getLocalBounds().width/2, height-50);
	//gameDoneMsg.setPosition(width / 2 - gameDoneMsg.getLocalBounds().width/2, height / 2-gameDoneMsg.getLocalBounds().height/2);
	//-----------------------

	//----variables
	const char winMsg[20] = "GAME OVER YOU WIN";
	const char loseMsg[20] = "GAME OVER YOU LOSE";
	const int MAX_ENEMIES = 6;
	int enemiesCount = 0;

	int playerSpd = 7;
	int enemySpd = 10;

	int fireRate = 10;
	int nextFire = fireRate;

	int createEnemyRate = 20;
	int nextCreateEnemy = createEnemyRate;

	int score = 0;
	//-----------------------

	while (app.isOpen())
	{
		Event event;
		if (app.pollEvent(event))
		{
			if (event.type == Event::EventType::Closed)
				app.close();
		}

		Vector2f speed = { 0.0f, 0.0f };
		if (!player.IsDie())
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
				speed.y = -playerSpd;
			if (Keyboard::isKeyPressed(Keyboard::Key::S))
				speed.y = playerSpd;
			if (Keyboard::isKeyPressed(Keyboard::Key::D))
				speed.x = playerSpd;
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
				speed.x = -playerSpd;

			player.move(speed);
		}

		if(nextFire < fireRate)
			nextFire++;
		if (nextCreateEnemy < createEnemyRate)
			nextCreateEnemy++;

		if (!player.IsDie() && Keyboard::isKeyPressed(Keyboard::Key::Space) && nextFire >= fireRate)
		{
			nextFire = 0;
			Bullet bullet = Bullet(10);
			bullet.ShootInit(player.getPosition());
			bullets.push_back(bullet);
		}
		//enemy create / Rate creation
		if (enemiesCount < MAX_ENEMIES && nextCreateEnemy >= createEnemyRate)
		{
			nextCreateEnemy = 0;

			srand(rand());
			int randX = rand() % width;

			Enemy enemy = Enemy(Color::Color(255, 145, 0));
			enemy.setPosition(randX, 0);
			enemies.push_back(enemy);

			enemiesCount++;
		}

		//SHOOT bullets mv
		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets[i].ShootForward())
			{
				bullets.erase(bullets.begin() + i);
			}
		}

		//ENEMY moving
		for (int i = 0; i < enemiesCount; i++)
		{
			if (!enemies[i].moveDownfall(enemySpd, height))
			{
				enemies.erase(enemies.begin() + i);
				enemiesCount--;
			}
		}

		//충돌 후 처리
		for (int i = 0; i < enemiesCount; i++)
		{
			//Bullet Collision
			for (int j = 0; j < bullets.size(); j++)
			{
				if (bullets[j].getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
				{
					bullets[j].stop();

					if (!enemies[i].isDie())
					{
						enemies[i].setDead();

						score++;
					}
				}
			}

			//Player Collision
			if (!enemies[i].isDie() && player.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
			{
				if (player.Hurt())
				{
					enemies[i].setDead(Color::Yellow);
				}
				else
				{
					gameDoneMsg.setString(loseMsg);
					gameDoneMsg.setPosition(width / 2 - gameDoneMsg.getLocalBounds().width / 2, height / 2 - gameDoneMsg.getLocalBounds().height / 2);
				}
			}
		}

		app.clear(Color::Color(217, 217, 217));
		
		//Draw bullets
		for (int i = 0; i < bullets.size(); i++)
			app.draw(bullets[i].getInstance());

		//Draw enemies
		for (int i = 0; i < enemies.size(); i++)
			app.draw(enemies[i].getInstance());

		app.draw(player.getInstance());

		healthText.setString("HEALTH/" + to_string(player.getHealth()));
		scoreText.setString("SCORE/" + to_string(score));

		//Draw UIs
		app.draw(scoreText);
		app.draw(healthText);
		if (player.IsDie()) app.draw(gameDoneMsg);

		app.display();
	}

	return 0;
}
