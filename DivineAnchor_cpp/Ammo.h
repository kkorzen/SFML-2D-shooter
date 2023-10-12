#pragma once
#include "Globals.h"
#include "Player.h"

class AmmoCrate :public Entity {
private:
	int maxCrateNumber = 1;
	int delayCounter = 0;

	vector<AmmoCrate> ammoCrates;

	void InitTexture();
	void InitSprite();

	void PickedUp(Player& player);

public:
	AmmoCrate();
	~AmmoCrate() = default;

	void SetCrateAmount(short x);
	void ClearVector();

	void Update(Player& player);
	void RenderCrate(RenderWindow& window);
};

class AmmoIcon :public Entity {
private:
	Font font;
	Text ammo;
	ostringstream ssAmmo;

	void InitTexture();
	void InitSprite();

	void InitFont();
	void InitAmmoCounter(Player& player);

public:
	AmmoIcon(Player& player);
	~AmmoIcon() = default;

	void Update(Player& player);
	void RenderAll(RenderWindow& window);
};