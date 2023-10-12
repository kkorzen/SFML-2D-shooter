#include "Background.h"

void Background::InitTexture() {
	this->texture.loadFromFile("Sprites/Background.png");
}

void Background::InitSprite() {
	this->sprite.setTexture(texture);
}

Background::Background() {
	this->InitTexture();
	this->InitSprite();
}

//============================================================================

void TeachScreen::InitTexture() {
	this->texture1.loadFromFile("Sprites/Help_page1.png");
	this->texture2.loadFromFile("Sprites/Help_page2.png");
}

void TeachScreen::InitSprite() {
	this->page1.setTexture(texture1);
	this->page2.setTexture(texture2);
}

TeachScreen::TeachScreen() {
	this->InitTexture();
	this->InitSprite();
}

void TeachScreen::RenderTeachScreen(RenderWindow& window) {
	if (this->helpPageNumber == 1) {
		this->RenderPageOne(window);
		if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			this->helpPageNumber = 2;
	}
	if (this->helpPageNumber == 2) {
		this->RenderPageTwo(window);
		if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			this->helpPageNumber = 1;
	}
}

void TeachScreen::RenderPageOne(RenderWindow& window) {
	window.draw(this->page1);
}

void TeachScreen::RenderPageTwo(RenderWindow& window) {
	window.draw(this->page2);
}