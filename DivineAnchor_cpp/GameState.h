#pragma once
#include"Globals.h"
#include "Entity.h"
#include "Score.h"

class Difficulty :public Entity {
private:
	Font font;
	Text diff[3];

	int selectedItem = 0;

	void InitTexture();
	void InitSprite();
	void InitFont();
	void InitOptions();
	
	void GoLeft();
	void GoRight();

	void Delay(int delay);

public:
	short diffSelectedFlag = 0;
	Difficulty();
	~Difficulty() = default;

	int GetSelectedItem();

	void Update(Event& evnt);
	void RenderDiff(RenderWindow& window);
};

class QuitGame :public Entity {
private:
	Font font;
	Text opt[2];

	int selectedItem = 0;

	void InitTexture();
	void InitSprite();
	void InitFont();
	void InitOptions();

	void GoLeft();
	void GoRight();

	void Delay(int delay);

public:
	short quitSelectedFlag = 0;
	QuitGame();
	~QuitGame() = default;

	int GetSelectedItem();

	void Update(Event & evnt);
	void RenderQuit(RenderWindow & window);
};

class DeathState :public Entity {
private:
	Text sumUp[2];
	Font font;

	void InitTexture();
	void InitSprite();
	void InitFont();
	void InitSumUp();

public:
	DeathState();
	~DeathState() = default;

	void Update(Difficulty& diff, Score& score);
	void RenderAll(RenderWindow& window);
};