#include<iostream>
#include<string>

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<SFML\Audio.hpp>

#include"Player.h"
#include"Enemy.h"
#include"Bullet.h"
#include"SoundManager.h"

using namespace std;
using namespace sf;

int main() {
	//srand(time(NULL));
	RenderWindow window(VideoMode(800, 600), "Space Ship Action", Style::Default);
	window.setFramerateLimit(60);

	SoundManager music;
	music.playBackgroundMusic();

	Texture background;
	background.loadFromFile("Textures/background.png");
	
	Sprite backImage;
	backImage.setTexture(background);

	Font font;
	font.loadFromFile("Fonts/Dosis-Light.ttf");

	//Init Texture
	Texture playerTex;
	playerTex.loadFromFile("Textures/ship.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Textures/enemy.png");

	Texture bulletTex;
	bulletTex.loadFromFile("Textures/missileTex01.png");

	//Player Init
	Player player(&playerTex);
	int shootTimer = 20;

	int enemyspawnTimer = 0;
	vector<Enemy> enemies;
	enemies.push_back(Enemy(&enemyTex, window.getSize()));

	Text hpText;
	hpText.setFont(font);
	hpText.setCharacterSize(12);
	hpText.setFillColor(Color::White);

	Text EhpText;
	EhpText.setFont(font);
	EhpText.setCharacterSize(12);
	EhpText.setFillColor(Color::White);

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(200.f, window.getSize().y / 2);
	gameOverText.setString("GameOver");
	
	int score = 0;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (player.HP > 0) {



			// Player
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
				player.shape.move(0.f, -10.f);
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-10.f, 0.f);
			if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0.f, 10.f);
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(10.f, 0.f);

			hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
			hpText.setString(to_string(player.HP) + "/" + to_string(player.HPMax));
			// Collision with window
			if (player.shape.getPosition().x <= 0)
				player.shape.setPosition(0.f, player.shape.getPosition().y);

			if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
				player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);

			if (player.shape.getPosition().y <= 0)
				player.shape.setPosition(player.shape.getPosition().x, 0.f);

			if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
				player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

			if (shootTimer < 15)
				shootTimer++;

			//Update
			if (Keyboard::isKeyPressed(Keyboard::Enter) && shootTimer >= 15)
			{
				player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
				shootTimer = 0;
			}

			//Enemy
			if (enemyspawnTimer < 30)
				enemyspawnTimer++;
			if (enemyspawnTimer >= 30)
			{
				enemies.push_back(Enemy(&enemyTex, window.getSize()));
				enemyspawnTimer = 0;
			}
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(-4.0f, 0.f);
				if (enemies[i].shape.getPosition().x <= -enemies[i].shape.getGlobalBounds().width)
					enemies.erase(enemies.begin() + i);

				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + i);
					player.HP--;
				}
			}

			scoreText.setString("Score: " + to_string(score));
		}
		window.clear();
		window.draw(backImage);
		window.draw(player.shape);
		for (auto& bullet : player.bullets)
		{
			window.draw(bullet.shape);
			music.playLazer();
		}
		// Out of screen
		for (size_t i = 0; i < player.bullets.size(); i++)
		{	// Move
			player.bullets[i].shape.move(15.f, 0.f);
			if (player.bullets[i].shape.getPosition().x > window.getSize().x)
			{
				player.bullets.erase(player.bullets.begin() + i);
				break;
			}

			for (size_t k = 0; k < enemies.size(); k++)
			{
				if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
				{
					if (--enemies[k].HP == 0)
					{
						score += enemies[k].HPMax;
						enemies.erase(enemies.begin() + k);
						music.playExplosion();
						music.playReward();
					}
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}
			}
		}

		for (auto& e : enemies)
		{
			EhpText.setString(to_string(e.HP) + "/" + to_string(e.HPMax));
			EhpText.setPosition(e.shape.getPosition().x, e.shape.getPosition().y - EhpText.getGlobalBounds().height);
			window.draw(EhpText);
			window.draw(e.shape);
		}
		window.draw(scoreText);
		window.draw(hpText);
		

		if (player.HP <= 0)
		{
			music.playExplosion();
			window.draw(gameOverText);
			music.pauseBackgroundMusic();
		}
		window.display();

	}
	return 0;
}