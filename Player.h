#pragma once

#include<iostream>
#include<vector>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

#include"Player.h"
#include"Bullet.h"


using namespace std;
using namespace sf;

class Player
{
public:
	vector<Bullet> bullets;
	Sprite shape;
	Texture *texture;
	int HP;
	int HPMax;
	Player(Texture* texture);
	~Player() {}

};
