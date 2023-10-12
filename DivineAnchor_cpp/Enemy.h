#pragma once
#include "Player.h"

class Enemy : public Entity {
	friend class Player;
private:
	Texture textureL;
	Texture textureR;

	int enemy_counter;
	int max_enemy_no = 1;

	vector<Enemy> enemies;

	void InitTextureL();
	void InitTextureR();
	void InitSprite();

	void LookAt(Player& player);
	void Follow(Player& player);

	void ChangeTexture(Player& player);

	void Delay();

public:
	Enemy();
	~Enemy() = default;

	void SetEnemiesAmount(short x);
	void ClearVector();

	void Update(Player& player);
	void Spawn(Player& player, RenderWindow& window);
};