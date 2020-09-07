#include "Player.h"


Player::Player(Texture *texture)
{
	this->HPMax = 10;
	this->HP = this->HPMax;

	this->texture = texture;
	this->shape.setTexture(*texture);

	this->shape.setScale(0.1f, 0.1f);
	this->shape.setPosition(0.f, 0.f);
}
