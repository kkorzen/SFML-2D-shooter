#include "Player.h"

void Player::InitTexture() {
	this->texture.loadFromFile("Sprites/Player.png");
}

void Player::InitSprtie() {
	this->sprite.setTexture(texture);
	this->sprite.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	this->sprite.setOrigin(static_cast<float>(this->texture.getSize().x / 2), static_cast<float>(this->texture.getSize().y / 2));
}

void Player::MoveUp() {
	if (Keyboard::isKeyPressed(Keyboard::Key::W) && this->sprite.getPosition().y - this->texture.getSize().y / 2 > 0)
		this->sprite.move(0.0f, -10.0f);
}

void Player::MoveDown() {
	if (Keyboard::isKeyPressed(Keyboard::Key::S) && this->sprite.getPosition().y + this->texture.getSize().y / 2 < WIN_HEIGHT)
		this->sprite.move(0.f, 10.f);
}

void Player::MoveLeft() {
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && this->sprite.getPosition().x - this->texture.getSize().x / 2 > 0)
		this->sprite.move(-10.f, 0.f);
}

void Player::MoveRight() {
	if (Keyboard::isKeyPressed(Keyboard::Key::D) && this->sprite.getPosition().x + this->texture.getSize().x / 2 < WIN_WIDTH)
		this->sprite.move(10.f, 0.f);
}

void Player::Move() {
	this->MoveUp();
	this->MoveDown();
	this->MoveLeft();
	this->MoveRight();
}

void Player::LookAt(Window& window) {
	Vector2f window_mouse_pos = Vector2f(Mouse::getPosition(window));
	float dx = this->sprite.getPosition().x - window_mouse_pos.x;
	float dy = this->sprite.getPosition().y - window_mouse_pos.y;
	float rotation_angle = static_cast<float>(atan2(dy, dx) * (180 / M_PI));
	this->sprite.setRotation(rotation_angle);
}

void Player::Shoot(Window& window, Bullet& bullet, Clock& clock) {
	Vector2f mouse_pos_window = Vector2f(Mouse::getPosition(window));
	Vector2f player_center = this->sprite.getPosition();

	Vector2f aim_dir = mouse_pos_window - player_center;
	Vector2f aim_dir_norm = aim_dir / static_cast<float>(sqrt(pow(aim_dir.x, 2) + pow(aim_dir.y, 2)));

	bullet.currentVelocity = aim_dir_norm * bullet.maxSpeed;

	if (Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asMilliseconds() > 100.f && this->currentMagazine > 0) {
		bullet.sprite.setPosition(player_center);
		bullet.sprite.setRotation(this->sprite.getRotation());
		bullets.push_back(Bullet(bullet));
		clock.restart();
		this->currentMagazine--;
	}
}

void Player::Collision(Enemy& enemy, Score& score) {
	for (size_t i = 0; i < this->bullets.size(); i++) {
		if (this->bullets[i].sprite.getPosition().x <0 ||
			this->bullets[i].sprite.getPosition().x > WIN_WIDTH ||
			this->bullets[i].sprite.getPosition().y<0 ||
			this->bullets[i].sprite.getPosition().y>WIN_HEIGHT)
		{
			this->bullets.erase(this->bullets.begin() + i);
		}
		else {
			for (size_t j = 0; j < enemy.enemies.size(); j++) {
				if (this->bullets[i].sprite.getGlobalBounds().intersects(enemy.enemies[j].sprite.getGlobalBounds())) {
					this->bullets.erase(this->bullets.begin() + i);
					enemy.enemies.erase(enemy.enemies.begin() + j);
					score.ScoreUp();
					break;
				}
			}
		}
	}

	for (size_t i = 0; i < enemy.enemies.size(); i++) {
		if (this->sprite.getGlobalBounds().intersects(enemy.enemies[i].sprite.getGlobalBounds()) && this->currentHP > 0) {
			this->currentHP--;
			enemy.enemies.erase(enemy.enemies.begin() + i);
		}
	}
}


Player::Player() {
	this->InitTexture();
	this->InitSprtie();
}

int Player::getCurrentHP() {
	return this->currentHP;
}

void Player::IncrementHP() {
	this->currentHP++;
}

void Player::SetHP(short x) {
	this->currentHP = x;
}

void Player::SetAmmo(short x)
{
	this->currentMagazine = x;
}
int Player::GetCurrentAmmo() {
	return this->currentMagazine;
}

void Player::IncreaseAmmo() {
	this->currentMagazine += 15;
}

void Player::SetAmmoToMax() {
	this->currentMagazine = 30;
}

void Player::SetPos(Vector2f pos) {
	this->sprite.setPosition(pos);
}

FloatRect Player::ReturnGlobalBounds() {
	return this->sprite.getGlobalBounds();
}

void Player::ClearVector() {
	this->bullets.clear();
}

void Player::Update(RenderWindow& window, Bullet& bullet, Clock& clock, Enemy& enemy, Score& score) {
	this->Move();
	this->LookAt(window);
	this->Shoot(window, bullet, clock);
	this->Collision(enemy, score);
}

void Player::RenderShooting(RenderWindow& window) {
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i].Move();
		bullets[i].Render(window);
	}
}