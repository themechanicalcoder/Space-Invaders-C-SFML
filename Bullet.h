#pragma once
#include<iostream>
#include<vector>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>


using namespace std;
using namespace sf;

class Bullet
{
public:
	Sprite shape;

	Bullet(Texture* texture, Vector2f position);
	~Bullet() {}

};

