#include "Ammo.h"

void AmmoCrate::InitTexture() {
	if (!this->texture.loadFromFile("Sprites/ammo.png")) {
		cout << "Ammo Crate texture not loaded.\n";
	}
}

void AmmoCrate::InitSprite() {
	this->sprite.setOrigin(float(texture.getSize().x / 2), float(texture.getSize().y / 2));
	this->sprite.setPosition(random(WIN_WIDTH, 50), random(WIN_HEIGHT, 50));
}

AmmoCrate::AmmoCrate() {
	this->InitTexture();
	this->InitSprite();
}

void AmmoCrate::PickedUp(Player& player) {
	for (size_t i = 0; i < ammoCrates.size(); i++) {
		if (player.ReturnGlobalBounds().intersects(this->ammoCrates[i].sprite.getGlobalBounds())) {
			if (player.GetCurrentAmmo() <= 15 && player.GetCurrentAmmo() >= 0)
				player.IncreaseAmmo();
			else if (player.GetCurrentAmmo() > 15 && player.GetCurrentAmmo() < 30)
				player.SetAmmoToMax();
			this->ammoCrates.erase(this->ammoCrates.begin() + i);
		}
	}
}

void AmmoCrate::SetCrateAmount(short x) {
	this->maxCrateNumber = x;
}

void AmmoCrate::ClearVector() {
	this->ammoCrates.clear();
}

void AmmoCrate::Update(Player& player) {
	this->PickedUp(player);
}

void AmmoCrate::RenderCrate(RenderWindow& window) {
	if (this->delayCounter < 6 * FPS)
		this->delayCounter++;

	if (this->delayCounter >= 6 * FPS && this->ammoCrates.size() < this->maxCrateNumber) {
		this->ammoCrates.push_back(AmmoCrate());
		this->delayCounter = 0;
	}

	for (size_t i = 0; i < this->ammoCrates.size(); i++) {
		this->ammoCrates[i].sprite.setTexture(texture);
		this->ammoCrates[i].Render(window);
	}
}

void AmmoIcon::InitTexture() {
	this->texture.loadFromFile("Sprites/ammoIcon.png");
}

void AmmoIcon::InitSprite() {	
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.17f, 0.17f);
	this->sprite.setPosition(20.f, 128*0.7 + 20);
}

void AmmoIcon::InitFont() {
	this->font.loadFromFile("Fonts/Arial.ttf");
}

void AmmoIcon::InitAmmoCounter(Player& player) {
	this->ssAmmo << player.GetCurrentAmmo();

	this->ammo.setFont(font);
	this->ammo.setCharacterSize(30);
	this->ammo.setFillColor(Color(204, 82, 0));
	this->ammo.setOutlineColor(Color::Black);
	this->ammo.setOutlineThickness(5);
	this->ammo.setString(ssAmmo.str());
}

AmmoIcon::AmmoIcon(Player& player) {
	this->InitTexture();
	this->InitSprite();

	this->InitFont();
	this->InitAmmoCounter(player);
}

void AmmoIcon::Update(Player& player) {
	if (player.GetCurrentAmmo() >= 10)
		this->ammo.setPosition(this->sprite.getPosition().x + double(this->texture.getSize().x) * this->sprite.getScale().x / 3.5, this->sprite.getPosition().y + double(this->texture.getSize().y) * this->sprite.getScale().y / 3.5);
	if(player.GetCurrentAmmo() < 10)
		this->ammo.setPosition(this->sprite.getPosition().x + double(this->texture.getSize().x) * this->sprite.getScale().x / 2.5, this->sprite.getPosition().y + double(this->texture.getSize().y) * this->sprite.getScale().y / 3.5);

	this->ssAmmo.str("");
	this->ssAmmo << player.GetCurrentAmmo();
	this->ammo.setString(ssAmmo.str());
}

void AmmoIcon::RenderAll(RenderWindow& window) {
	this->Render(window);
	window.draw(this->ammo);
}