#pragma once

#include<iostream>
#include<vector>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

using namespace sf;
class Enemy
{
public:
	Sprite shape;
	int HP;
	int HPMax;
	Enemy(Texture* texture, Vector2u windowSize);
};

