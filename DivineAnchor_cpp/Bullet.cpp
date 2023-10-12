#include "Bullet.h"

void Bullet::InitTexture() {
	this->texture.loadFromFile("Sprites/bullet.png");
}

void Bullet::InitSprite() {
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(float(texture.getSize().x / 2), float(texture.getSize().y / 2));
}

void Bullet::Move() {
	this->sprite.move(currentVelocity);
}

Bullet::Bullet(float maxS) {
	this->maxSpeed = maxS;
	this->InitTexture();
	this->InitSprite();
}