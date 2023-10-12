#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "HP.h"
#include "Ammo.h"
#include "Score.h"

class Player :public Entity {
	friend class Enemy;
private:
	int maxMagazine = 30;
	int currentMagazine = maxMagazine;
	int maxHP = 4;
	int currentHP = maxHP;

	vector<Bullet> bullets;

	void InitTexture();
	void InitSprtie();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Move();

	void LookAt(Window& window);

	void Shoot(Window& window, Bullet& bullet, Clock& clock);

	void Collision(Enemy& enemy, Score& score);


public:
	Player();
	~Player() = default;

	int getCurrentHP();
	void IncrementHP();
	void SetHP(short x);
	void SetAmmo(short x);

	int GetCurrentAmmo();
	void IncreaseAmmo();
	void SetAmmoToMax();

	void SetPos(Vector2f pos);

	FloatRect ReturnGlobalBounds();
	void ClearVector();

	void Update(RenderWindow& window, Bullet& bullet, Clock& clock, Enemy& enemy, Score& score);
	void RenderShooting(RenderWindow& window);
};