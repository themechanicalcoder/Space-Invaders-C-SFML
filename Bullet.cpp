#include "Bullet.h"
Bullet::Bullet(Texture* texture, Vector2f position) 
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.03f, 0.03f);
	position.y += 25;
	position.x += 40;
	this->shape.setPosition(position);
} 