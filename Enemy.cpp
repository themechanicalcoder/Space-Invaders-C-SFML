#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2u windowSize)
{
	this->HPMax = rand() % 3 + 1;
	this->HP = this->HPMax;
	this->shape.setTexture(*texture);
	this->shape.setScale(0.1f, 0.1f);
	this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));

}
