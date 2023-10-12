#include "MainMenu.h"

void MainMenu::InitTexture(){
	if (!this->texture.loadFromFile("Sprites/MenuPic.png"))
		cout << "MainMenu::InitTexture not loaded";
}

void MainMenu::InitFont() {
	if (!this->font.loadFromFile("Fonts/DiabloHeavy.ttf"))
		cout << "MainMenu::InitFont not loaded";
}

void MainMenu::InitSprite(){
	this->sprite.setTexture(texture);
}

void MainMenu::InitMenu() {
	menu[0].setFont(font);
	menu[0].setFillColor(Color(159, 5, 0));
	menu[0].setString("New Game");
	menu[0].setPosition(Vector2f(this->texture.getSize().x / 6 - 50, this->texture.getSize().y - 200));
	menu[0].setOutlineThickness(5);
	menu[1].setFont(font);
	menu[1].setFillColor(Color(51, 0, 0));
	menu[1].setString("Best Players");
	menu[1].setPosition(Vector2f(this->texture.getSize().x * 3 / 6 - 50, this->texture.getSize().y - 200));
	menu[1].setOutlineThickness(5);
	menu[2].setFont(font);
	menu[2].setFillColor(Color(51, 0, 0));
	menu[2].setString("Exit");
	menu[2].setPosition(Vector2f(this->texture.getSize().x * 5 / 6 - 50, this->texture.getSize().y - 200));
	menu[2].setOutlineThickness(5);
}

void MainMenu::GoLeft() {
	if (selectedItem >= 0 && selectedItem < 3) {
		menu[selectedItem].setFillColor(Color(51, 0, 0));
		menu[selectedItem].setStyle(Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = 3 - 1;
		menu[selectedItem].setFillColor(Color(159, 5, 0));
		menu[selectedItem].setStyle(Text::Bold);
	}
}

void MainMenu::GoRight() {
	if (selectedItem >= 0 && selectedItem < 3) {
		menu[selectedItem].setFillColor(Color(51, 0, 0));
		menu[selectedItem].setStyle(Text::Regular);
		selectedItem++;
		if (selectedItem >= 3)
			selectedItem = 0;
		menu[selectedItem].setFillColor(Color(159, 5, 0));
		menu[selectedItem].setStyle(Text::Bold);
	}
}

void MainMenu::Delay(int delay)
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

MainMenu::MainMenu() {
	this->InitTexture();
	this->InitFont();
	this->InitSprite();
	this->InitMenu();
}

int MainMenu::GetSelectedItem() {
	return this->selectedItem;
}

void MainMenu::Update(Event& evnt, RenderWindow& window) {
	if (evnt.type == Event::KeyPressed) {
		switch (evnt.key.code) {
		case Keyboard::Key::Left:
			Delay(50); this->GoLeft(); break;
		case Keyboard::Key::Right:
			Delay(50); this->GoRight(); break;
		}
		if (this->menuSelectedFlag == 0) {
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 0) {
				this->menuSelectedFlag = 1;
			}
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 1) {
				this->menuSelectedFlag = 2;
			}
			if (evnt.key.code == Keyboard::Key::Enter && this->selectedItem == 2) {
				window.close();
			}
		}
	}
}

void MainMenu::RenderMenu(RenderWindow& window) {
	this->Render(window);
	for (int i = 0; i < 3; i++) {
		window.draw(this->menu[i]);
	}
}

