#pragma once
#include "Globals.h"
#include "Entity.h"

class Background :public Entity {
private:
	void InitTexture();
	void InitSprite();

public:
	Background();
	~Background() = default;
};

class TeachScreen {
private:
	Texture texture1;
	Texture texture2;

	Sprite page1;
	Sprite page2;

	int helpPageNumber = 1;

	void InitTexture();
	void InitSprite();

	void RenderPageOne(RenderWindow& window);
	void RenderPageTwo(RenderWindow& window);

public:
	TeachScreen();
	~TeachScreen() = default;

	void RenderTeachScreen(RenderWindow& window);
};