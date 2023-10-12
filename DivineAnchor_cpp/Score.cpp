#include "Score.h"

void Score::InitFont() {
	this->font.loadFromFile("Fonts/Arial.ttf");
}

void Score::InitScore() {
	this->ssScore << "Score: " << this->scoreNumber;

	this->score.setFont(font);
	this->score.setCharacterSize(30);
	this->score.setPosition(0.8 * WIN_WIDTH, 5.f);
	this->score.setFillColor(Color::Red);
	this->score.setOutlineColor(Color::Black);
	this->score.setOutlineThickness(5);
	this->score.setString(ssScore.str());
}

Score::Score() {
	this->InitFont();
	this->InitScore();
}

int Score::GetScore() {
	return this->scoreNumber;
}

void Score::ScoreUp() {
	this->scoreNumber++;
	this->ssScore.str("");
	this->ssScore << "Score: " << this->scoreNumber;
	this->score.setString(ssScore.str());
}

void Score::ResetScore() {
	this->scoreNumber = 0;
	this->ssScore.str("");
	this->ssScore << "Score: " << scoreNumber;
	this->score.setString(ssScore.str());
}

void Score::Render(RenderWindow& window) {
	window.draw(this->score);
}