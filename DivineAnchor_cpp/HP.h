#pragma once
#include "Globals.h"
#include "Player.h"

class HPCrate :public Entity {
private:
	int maxCrateNumber = 1;
	int delayCounter=0;

	vector<HPCrate> hpCrates;

	void InitTexture();
	void InitSprite();

	void PickedUp(Player& player);
	
public:
	HPCrate();
	~HPCrate() = default;

	void SetCrateAmount(short x);
	void ClearVector();

	void Update(Player& player);
	void RenderCrate(RenderWindow& window);
};

class HPIcon :public Entity {
private:
	Sprite hpIcon[4];

	void InitTexture();
	void InitSprite();

public:
	HPIcon();
	~HPIcon() = default;

	Vector2u GetTextureSize();

	void RenderIcon(RenderTarget& target, Player& player);
};