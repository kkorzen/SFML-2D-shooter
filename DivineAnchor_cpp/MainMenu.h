#pragma once
#include "Globals.h"
#include "Entity.h"

class MainMenu :public Entity{
protected:
	Font font;
	Text menu[3];
	
	int selectedItem = 0;

	void InitTexture();
	void InitSprite();

	void InitFont();
	void InitMenu();
	
	void GoLeft();
	void GoRight();

	void Delay(int delay);

public:
	int menuSelectedFlag = 0;

	MainMenu();
	~MainMenu() = default;

	int GetSelectedItem();

	void Update(Event& evnt, RenderWindow& window);
	void RenderMenu(RenderWindow& window);
};