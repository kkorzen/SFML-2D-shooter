#include "Enemy.h"

void Enemy::InitTextureL() {
	this->textureL.loadFromFile("Sprites/Enemy_l.png");
}

void Enemy::InitTextureR() {
	this->textureR.loadFromFile("Sprites/Enemy_r.png");
}

void Enemy::InitSprite() {
	float angle = random(2 * M_PI);
	this->sprite.setTexture(textureL);
	this->sprite.setOrigin(float(textureL.getSize().x / 2), float(textureL.getSize().y / 2));
	this->sprite.setPosition(0.5*WIN_WIDTH*cos(angle),0.75*WIN_WIDTH*sin(angle));
}

void Enemy::LookAt(Player& player) {
	Vector2f enemy_pos = this->sprite.getPosition();
	Vector2f player_pos = player.sprite.getPosition();
	float dx = enemy_pos.x - player_pos.x;
	float dy = enemy_pos.y - player_pos.y;
	float rotation_angle = static_cast<float>(atan2(dy, dx) * (180 / M_PI));
	this->sprite.setRotation(rotation_angle);
}

void Enemy::Follow(Player& player) {
	Vector2f enemy_center = this->sprite.getPosition();
	Vector2f player_center = player.sprite.getPosition();
	Vector2f go_dir = player_center - enemy_center;
	Vector2f go_dir_norm = go_dir / static_cast<float>(sqrt(pow(go_dir.x, 2) + pow(go_dir.y, 2)));

	this->LookAt(player);
	this->sprite.move(go_dir_norm * 4.f);
}

void Enemy::ChangeTexture(Player& player) {
	if (this->sprite.getPosition().x >= player.sprite.getPosition().x) {
		this->sprite.setTexture(textureR);
	}
	if (this->sprite.getPosition().x < player.sprite.getPosition().x) {
		this->sprite.setTexture(textureL);
	}
}

void Enemy::Delay() {
	if (this->enemy_counter < 20)
		this->enemy_counter++;
}

Enemy::Enemy() {
	this->InitTextureL();
	this->InitTextureR();
	this->InitSprite();
}

void Enemy::SetEnemiesAmount(short x) {
	this->max_enemy_no = x;
}

void Enemy::ClearVector() {
	this->enemies.clear();
}

void Enemy::Update(Player& player) {
	Follow(player);
	ChangeTexture(player);
}

void Enemy::Spawn(Player& player, RenderWindow& window) {
	this->Delay();

	if (this->enemy_counter >= FPS/3 && this->enemies.size() < this->max_enemy_no) {
		this->enemies.push_back(Enemy());
		this->enemy_counter = 0;
	}

	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].Update(player);
		this->enemies[i].Render(window);
	}
}
