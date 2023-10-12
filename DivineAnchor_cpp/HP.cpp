#include "HP.h"

void HPCrate::InitTexture() {
	if (!this->texture.loadFromFile("Sprites/HP.png")) {
		cout << "Health Point texture not loaded.\n";
	}
}

void HPCrate::InitSprite() {
	this->sprite.setOrigin(float(texture.getSize().x / 2), float(texture.getSize().y / 2));
	this->sprite.setPosition(random(WIN_WIDTH, 50), random(WIN_HEIGHT, 50));
	this->sprite.setScale(1.5, 1.5);
}

void HPCrate::PickedUp(Player& player) {
	for (size_t i = 0; i < hpCrates.size(); i++) {
		if (player.ReturnGlobalBounds().intersects(this->hpCrates[i].sprite.getGlobalBounds())) {
			if ((player.getCurrentHP() < 4 && player.getCurrentHP() > 0))
				player.IncrementHP();
			this->hpCrates.erase(this->hpCrates.begin() + i);
		}
	}
}

HPCrate::HPCrate() {
	this->InitTexture();
	this->InitSprite();
}

void HPCrate::SetCrateAmount(short x) {
	this->maxCrateNumber = x;
}

void HPCrate::ClearVector() {
	this->hpCrates.clear();
}

void HPCrate::Update(Player& player) {
	this->PickedUp(player);
}

void HPCrate::RenderCrate(RenderWindow& window) {
	if (this->delayCounter < 10 * FPS)
		this->delayCounter++;

	if (this->delayCounter >= 10 * FPS && this->hpCrates.size() < this->maxCrateNumber) {
		this->hpCrates.push_back(HPCrate());
		this->delayCounter = 0;
	}

	for (size_t i = 0; i < this->hpCrates.size(); i++) {
		this->hpCrates[i].sprite.setTexture(texture);
		this->hpCrates[i].Render(window);
	}	
}

void HPIcon::InitTexture() {
	this->texture.loadFromFile("Sprites/HPicon.png");
}

void HPIcon::InitSprite() {
	for (int i = 0; i < 4; i++) {
		this->hpIcon[i].setTexture(texture);
		this->hpIcon[i].setScale(0.7, 0.7);
		this->hpIcon[i].setPosition(i * this->texture.getSize().x * this->hpIcon[i].getScale().x, 0);
	}
}

HPIcon::HPIcon() {
	this->InitTexture();
	this->InitSprite();
}

Vector2u HPIcon::GetTextureSize() {
	return this->texture.getSize();
}

void HPIcon::RenderIcon(RenderTarget& target, Player& player) {
	for (int i = 0; i < player.getCurrentHP(); i++) {
		target.draw(this->hpIcon[i]);
	}
}