#include "GameState.h"

void Difficulty::InitTexture() {
	if (!this->texture.loadFromFile("Sprites/DiffPic.jpg"))
		cout << "Difficulty::InitTexture not loaded";
}

void Difficulty::InitFont() {
	if (!this->font.loadFromFile("Fonts/DiabloHeavy.ttf"))
		cout << "Difficulty::InitFont not loaded";
}

void Difficulty::InitSprite() {
	this->sprite.setTexture(texture);
}

void Difficulty::InitOptions() {
	diff[0].setFont(font);
	diff[0].setFillColor(Color(159, 5, 0));
	diff[0].setString("Easy:\n Enemies at once: 4\n Ammo Crates at once: 1\n MediBags at once: 2");
	diff[0].setPosition(Vector2f(100.f, 150.f));
	diff[0].setOutlineThickness(5);
	diff[1].setFont(font);
	diff[1].setFillColor(Color(51, 0, 0));
	diff[1].setString("Normal:\n Enemies amount depends on current score\n Ammo Crates at once: 2\n MediBags at once: 1");
	diff[1].setPosition(Vector2f(100.f, 350.f));
	diff[1].setOutlineThickness(5);
	diff[2].setFont(font);
	diff[2].setFillColor(Color(51, 0, 0));
	diff[2].setString("Insane:\n Enemies amount depends on current score\n Ammo Crates at ones: 1\n No MediBags");
	diff[2].setPosition(Vector2f(100.f, 550.f));
	diff[2].setOutlineThickness(5);
}

void Difficulty::GoLeft() {
	if (selectedItem >= 0 && selectedItem < 3) {
		diff[selectedItem].setFillColor(Color(51, 0, 0));
		diff[selectedItem].setStyle(Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = 3 - 1;
		diff[selectedItem].setFillColor(Color(159, 5, 0));
		diff[selectedItem].setStyle(Text::Bold);
	}
}

void Difficulty::GoRight() {
	if (selectedItem >= 0 && selectedItem < 3) {
		diff[selectedItem].setFillColor(Color(51, 0, 0));
		diff[selectedItem].setStyle(Text::Regular);
		selectedItem++;
		if (selectedItem >= 3)
			selectedItem = 0;
		diff[selectedItem].setFillColor(Color(159, 5, 0));
		diff[selectedItem].setStyle(Text::Bold);
	}
}

void Difficulty::Delay(int delay)
{
	sf::Clock zegar;
	sf::Time czas;
	while (true)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > delay)
		{
			zegar.restart();
			break;
		}

	}
}

Difficulty::Difficulty() {
	this->InitTexture();
	this->InitFont();
	this->InitSprite();
	this->InitOptions();
}

int Difficulty::GetSelectedItem() {
	return this->selectedItem;
}

void Difficulty::Update(Event& evnt) {
	if (evnt.type == Event::KeyPressed) {
		switch (evnt.key.code) {
		case Keyboard::Key::Up:
			Delay(50); this->GoLeft(); break;
		case Keyboard::Key::Down:
			Delay(50); this->GoRight(); break;
		}
		if (this->diffSelectedFlag == 0) {
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 0) {
				this->diffSelectedFlag = 1;
			}
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 1) {
				this->diffSelectedFlag = 2;
			}
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 2) {
				this->diffSelectedFlag = 3;
			}
		}
	}
}

void Difficulty::RenderDiff(RenderWindow& window) {
	this->Render(window);
	for (int i = 0; i < 3; i++) {
		window.draw(this->diff[i]);
	}
}

//========================================================================
//========================================================================
//========================================================================
//========================================================================

void QuitGame::InitTexture() {
	if (!this->texture.loadFromFile("Sprites/QuitPic.jpg"))
		cout << "QuitGame::InitTexture not loaded";
}

void QuitGame::InitFont() {
	if (!this->font.loadFromFile("Fonts/DiabloHeavy.ttf"))
		cout << "QuitGame::InitFont not loaded";
}

void QuitGame::InitSprite() {
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	this->sprite.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void QuitGame::InitOptions() {
	opt[0].setFont(font);
	opt[0].setFillColor(Color(159, 5, 0));
	opt[0].setString("No");
	opt[0].setPosition(Vector2f(WIN_WIDTH / 4, 500.f));
	opt[0].setCharacterSize(80);
	opt[0].setOutlineThickness(5);
	opt[1].setFont(font);
	opt[1].setFillColor(Color(51, 0, 0));
	opt[1].setString("Yes");
	opt[1].setPosition(Vector2f(WIN_WIDTH / 1.5 , 500.f));
	opt[1].setCharacterSize(80);
	opt[1].setOutlineThickness(5);
}

void QuitGame::GoLeft() {
	if (selectedItem >= 0 && selectedItem < 2) {
		opt[selectedItem].setFillColor(Color(51, 0, 0));
		opt[selectedItem].setStyle(Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = 2 - 1;
		opt[selectedItem].setFillColor(Color(159, 5, 0));
		opt[selectedItem].setStyle(Text::Bold);
	}
}

void QuitGame::GoRight() {
	if (selectedItem >= 0 && selectedItem < 2) {
		opt[selectedItem].setFillColor(Color(51, 0, 0));
		opt[selectedItem].setStyle(Text::Regular);
		selectedItem++;
		if (selectedItem >= 2)
			selectedItem = 0;
		opt[selectedItem].setFillColor(Color(159, 5, 0));
		opt[selectedItem].setStyle(Text::Bold);
	}
}

void QuitGame::Delay(int delay)
{
	sf::Clock zegar;
	sf::Time czas;
	while (true)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > delay)
		{
			zegar.restart();
			break;
		}

	}
}

QuitGame::QuitGame() {
	this->InitTexture();
	this->InitFont();
	this->InitSprite();
	this->InitOptions();
}

int QuitGame::GetSelectedItem() {
	return this->selectedItem;
}

void QuitGame::Update(Event& evnt) {
	if (evnt.type == Event::KeyPressed) {
		switch (evnt.key.code) {
		case Keyboard::Key::Left:
			Delay(50); this->GoLeft(); break;
		case Keyboard::Key::Right:
			Delay(50); this->GoRight(); break;
		}
		if (this->quitSelectedFlag == 0) {
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 0) {
				this->quitSelectedFlag = 1;
			}
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 1) {
				this->quitSelectedFlag = 2;
			}
		}
	}
}

void QuitGame::RenderQuit(RenderWindow& window) {
	this->Render(window);
	for (int i = 0; i < 2; i++) {
		window.draw(this->opt[i]);
	}
}

//========================================================================
//========================================================================
//========================================================================
//========================================================================

void DeathState::InitTexture() {
	this->texture.loadFromFile("Sprites/dw.jpg");
}

void DeathState::InitSprite() {
	this->sprite.setTexture(this->texture);
}

void DeathState::InitFont() {
	this->font.loadFromFile("Fonts/DiabloHeavy.ttf");
}

void DeathState::InitSumUp() {
	this->sumUp[0].setFont(font);
	this->sumUp[0].setFillColor(Color(159, 5, 0));
	this->sumUp[0].setPosition(Vector2f(WIN_WIDTH / 4, 200.f));
	this->sumUp[0].setCharacterSize(40);
	this->sumUp[0].setOutlineThickness(5);
	this->sumUp[1].setFont(font);
	this->sumUp[1].setFillColor(Color(159, 5, 0));
	this->sumUp[1].setPosition(Vector2f(WIN_WIDTH / 4, 250.f));
	this->sumUp[1].setCharacterSize(40);
	this->sumUp[1].setOutlineThickness(5);
}

DeathState::DeathState() {
	this->InitTexture();
	this->InitSprite();
	this->InitFont();
	this->InitSumUp();
}

void DeathState::Update(Difficulty& diff, Score& score) {
	switch (diff.diffSelectedFlag) {
	case 0: break;
	case 1: this->sumUp[0].setString("Chosen difficulty: Easy"); break;
	case 2: this->sumUp[0].setString("Chosen difficulty: Normal"); break;
	case 3: this->sumUp[0].setString("Chosen difficulty: Insane"); break;
	}
	this->sumUp[1].setString("Your score: " + to_string(score.GetScore()));
}

void DeathState::RenderAll(RenderWindow& window) {
	this->Render(window);
	for (int i = 0; i < 2; i++) {
		window.draw(this->sumUp[i]);
	}
}