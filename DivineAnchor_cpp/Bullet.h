#pragma once
#include "Globals.h"
#include "Entity.h"

class Bullet :public Entity {
	friend class Player;
private:
	Vector2f currentVelocity;
	float maxSpeed;

	void InitTexture();
	void InitSprite();
	
	void Move();

public:
	Bullet(float maxS);
	~Bullet() = default;
};