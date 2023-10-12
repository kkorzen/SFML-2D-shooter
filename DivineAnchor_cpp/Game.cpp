#include "Game.h"

void Game::InitWindow() {
	this->window = new RenderWindow(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Divine Anchor", Style::Default);
	this->window->setFramerateLimit(FPS);
}

void Game::InitClock() {
	this->clock = new Clock();
}

void Game::InitMainMenu() {
	this->mainMenu = new MainMenu();
}

void Game::InitDiffMenu() {
	this->diffMenu = new Difficulty();
}

void Game::InitQuitGame() {
	this->qgScreen = new QuitGame();
}

void Game::InitDeathScreen() {
	this->deathScreen = new DeathState();
}

void Game::InitPlayer() {
	this->player = new Player();
}

void Game::InitBullet() {
	this->bullet = new Bullet(15.f);
}

void Game::InitEnemy() {
	this->enemy = new Enemy();
}

void Game::InitHPCrate() {
	this->hpCrate = new HPCrate();
}

void Game::InitHPIcon() {
	this->hpIcon = new HPIcon();
}

void Game::InitScore() {
	this->score = new Score();
}

void Game::InitAmooCrate() {
	this->ammoCrate = new AmmoCrate();
}

void Game::InitAmmoIcon(Player& player) {
	this->ammoIcon = new AmmoIcon(player);
}

void Game::InitBackground() {
	this->bg = new Background();
}

void Game::InitTeachScreen() {
	this->ts = new TeachScreen();
}

void Game::InitTextBox() {
	this->tBox = new TextBox();
}

void Game::InitBestPlayers() {
	this->bestPlayers = new BestPlayers();
}

void Game::IncreaseEnemyNumber(Score* score) {
	if (score->GetScore() >= 0 && score->GetScore() < 20)
		this->enemy->SetEnemiesAmount(4);
	if (score->GetScore() >= 20 && score->GetScore() < 40)
		this->enemy->SetEnemiesAmount(5);
	if (score->GetScore() >= 40 && score->GetScore() < 80)
		this->enemy->SetEnemiesAmount(6);
	if (score->GetScore() >= 80 && score->GetScore() < 100)
		this->enemy->SetEnemiesAmount(7);
	if (score->GetScore() >= 100)
		this->enemy->SetEnemiesAmount(8);
}

void Game::Reset() {
	this->gameStateFlag = 0;
	this->mainMenu->menuSelectedFlag = 0;
	this->isGameStateInitialized = false;
	this->qgScreen->quitSelectedFlag = 0;
	this->diffMenu->diffSelectedFlag = 0;
	this->isFileLoaded = false;
	this->isFileOpened = false;

	this->player->SetHP(4);
	this->player->SetAmmo(30);
	this->enemy->ClearVector();
	this->player->ClearVector();
	this->ammoCrate->ClearVector();
	this->hpCrate->ClearVector();
	this->score->ResetScore();
	this->player->SetPos({ WIN_WIDTH / 2, WIN_HEIGHT / 2 });
	this->tBox->ResetTextBox();
}

Game::Game() {
	srand(time(NULL));

	this->InitWindow();
	this->InitClock();

	this->InitMainMenu();
	this->InitDiffMenu();
	this->InitQuitGame();
	this->InitDeathScreen();

	this->InitPlayer();
	this->InitBullet();
	this->InitEnemy();
	this->InitHPCrate();
	this->InitHPIcon();
	this->InitScore();
	this->InitAmooCrate();
	this->InitAmmoIcon(*this->player);
	this->InitBackground();
	this->InitTeachScreen();

	this->InitTextBox();
	this->InitBestPlayers();

	this->bestPlayers->OpenFile();
}

Game::~Game() {
	this->bestPlayers->CloseFile();

	delete this->window;
	delete this->clock;

	delete this->mainMenu;
	delete this->diffMenu;
	delete this->qgScreen;
	delete this->deathScreen;

	delete this->player;
	delete this->bullet;
	delete this->enemy;
	delete this->hpCrate;
	delete this->hpIcon;
	delete this->score;
	delete this->ammoCrate;
	delete this->ammoIcon;
	delete this->bg;
	delete this->ts;

	delete this->tBox;
	delete this->bestPlayers;
}

void Game::Run() {
	while (this->window->isOpen()) {
		this->Update();
		this->Render();
	}
}

void Game::Update() {
	Event evnt;
	while (this->window->pollEvent(evnt)) {
		if (evnt.type == Event::Closed)
			this->window->close();
		
		if(this->gameStateFlag==0)
			this->mainMenu->Update(evnt, *this->window);
		if(this->gameStateFlag==5)
			this->diffMenu->Update(evnt);
		if (this->gameStateFlag == 6)
			this->qgScreen->Update(evnt);
		if (this->gameStateFlag == 4 &&  evnt.type == Event::TextEntered)
			this->tBox->Update(evnt);

		if (evnt.Event::KeyPressed && evnt.Event::key.code == Keyboard::Key::F1) {
			if (this->gameStateFlag == 1 && this->clock->getElapsedTime().asMilliseconds() > 400.f) {
				this->gameStateFlag = 2;
				clock->restart();
			}
			else if (this->gameStateFlag == 2 && this->clock->getElapsedTime().asMilliseconds() > 400.f) {
				this->gameStateFlag = 1;
				clock->restart();
			}
		}

		if (evnt.Event::KeyPressed && evnt.key.code == Keyboard::Key::Escape && this->gameStateFlag == 1 && this->clock->getElapsedTime().asMilliseconds() > 400.f) {
			this->gameStateFlag = 6;
			this->clock->restart();
		}

		if (evnt.Event::KeyPressed && evnt.key.code == Keyboard::Key::Escape && this->gameStateFlag == 3 && this->clock->getElapsedTime().asMilliseconds() > 400.f) {
			this->Reset();
			this->clock->restart();
		}
	}

	if (this->isGameStateInitialized == false) {
		switch (this->mainMenu->menuSelectedFlag) {
		case 0:
			this->gameStateFlag = 0; break;
		case 1:
			this->gameStateFlag = 5;
			this->isGameStateInitialized = true;
			break;
		case 2:
			this->gameStateFlag = 3; 
			break;
		}
	}

	switch (this->gameStateFlag) {
	case 0:
		// Menu is updating in the window.pollEvent() function
		break;

	case 1:
		this->player->Update(*this->window, *this->bullet, *this->clock, *this->enemy, *this->score);
		this->hpCrate->Update(*this->player);
		this->ammoCrate->Update(*this->player);
		this->ammoIcon->Update(*this->player);

		if (this->player->getCurrentHP() <= 0)
			this->gameStateFlag = 4;

		if (this->diffMenu->diffSelectedFlag == 2 || this->diffMenu->diffSelectedFlag == 3)
			this->IncreaseEnemyNumber(this->score);
		break;

	case 2:
		// Help screen is updating in the window.pollEvent() function
		break;

	case 3:
		// Input to file done in case 4

		if (this->isFileOpened == false) {
			this->bestPlayers->UpdateReading();
			this->isFileOpened = true;
		}

		if (this->isFileLoaded == false) {
			this->bestPlayers->Update();
			this->isFileLoaded = true;
			for (int i = 0; i < 30; i++) {
				cout << "======================" << endl;
				cout << this->bestPlayers->recs[i].difficulty << endl;
				cout << this->bestPlayers->recs[i].userName << endl;
				cout << this->bestPlayers->recs[i].userScore << endl;
				cout << endl;
			}
		}
		break;
		
	case 4:
		// TextBox update done in the window.pollEvent() function
		this->deathScreen->Update(*this->diffMenu, *this->score);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape) && this->clock->getElapsedTime().asMilliseconds() > 400.f) {
			this->Reset();
			this->clock->restart();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Enter) && this->tBox->GetTextBox().length() > 1 && this->tBox->GetTextBox()[this->tBox->GetTextBox().length()-1]!=27) {
			this->bestPlayers->UpdateSaving(*this->tBox, *this->diffMenu, *this->score);
			this->Reset();	
		}

		break;

	case 5:
		switch (this->diffMenu->diffSelectedFlag) {
		case 1:
			this->enemy->SetEnemiesAmount(4);
			this->hpCrate->SetCrateAmount(2);
			this->ammoCrate->SetCrateAmount(1);
			this->gameStateFlag = 1;
			break;
		case 2:
			this->hpCrate->SetCrateAmount(1);
			this->ammoCrate->SetCrateAmount(2);
			this->gameStateFlag = 1;
			break;
		case 3:
			this->hpCrate->SetCrateAmount(0);
			this->ammoCrate->SetCrateAmount(1);
			this->gameStateFlag = 1;
			break;
		}
	case 6:
		switch (this->qgScreen->quitSelectedFlag) {
		case 1:
			this->gameStateFlag = 1;
			this->qgScreen->quitSelectedFlag = 0;
			break;
		case 2:
			this->Reset();
			break;
		}
	}	
}

void Game::Render() {
	//Clear
	this->window->clear();

	//Draw
	switch (this->gameStateFlag) {
	case 0:
		this->mainMenu->RenderMenu(*this->window);
		break;

	case 1:
		this->bg->Render(*this->window);

		this->enemy->Spawn(*this->player, *this->window); // includes Enemy::Update()

		this->hpCrate->RenderCrate(*this->window);
		this->hpIcon->RenderIcon(*this->window, *this->player);

		this->player->Render(*this->window);
		this->player->RenderShooting(*this->window);

		this->score->Render(*this->window);

		this->ammoCrate->RenderCrate(*this->window);
		this->ammoIcon->RenderAll(*this->window);

		break;

	case 2:
		this->ts->RenderTeachScreen(*this->window);
		break;

	case 3:
		this->bestPlayers->RenderAll(*this->window);
		break;

	case 4:
		this->deathScreen->RenderAll(*this->window);
		this->tBox->RenderTextBox(*this->window);
		break;

	case 5:
		this->diffMenu->RenderDiff(*this->window); 
		break;

	case 6:
		this->qgScreen->RenderQuit(*this->window);
		break;
	}

	//Display
	this->window->display();
}