#pragma once
#include "Player.h"
#include "Background.h"
#include "MainMenu.h"
#include "BestPlayers.h"

class Game {
private:
	int gameStateFlag = 0; //0 = menu 1 = normal game, 2 = help screen, 3 = best players, 4 = death screen, 5 = choosing difficulty, 6 = quit?
	bool isGameStateInitialized = false;
	bool isFileOpened = false;
	bool isFileLoaded = false;

	RenderWindow* window;
	Clock* clock;

	MainMenu* mainMenu;
	Difficulty* diffMenu;
	QuitGame* qgScreen;
	DeathState* deathScreen;

	Player* player;
	Bullet* bullet;
	Enemy* enemy;
	HPCrate* hpCrate;
	HPIcon* hpIcon;
	Score* score;
	AmmoCrate* ammoCrate;
	AmmoIcon* ammoIcon;
	Background* bg;
	TeachScreen* ts;

	TextBox* tBox;
	BestPlayers* bestPlayers;

	void InitWindow();
	void InitClock();

	void InitMainMenu();
	void InitDiffMenu();
	void InitQuitGame();
	void InitDeathScreen();

	void InitPlayer();
	void InitBullet();
	void InitEnemy();
	void InitHPCrate();
	void InitHPIcon();
	void InitScore();
	void InitAmooCrate();
	void InitAmmoIcon(Player& player);
	void InitBackground();
	void InitTeachScreen();

	void InitTextBox();
	void InitBestPlayers();

	void IncreaseEnemyNumber(Score* score);
	void Reset();

public:
	Game();
	~Game();

	void Run();

	void Update();
	void Render();
};