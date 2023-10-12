#include "TextBox.h"

void TextBox::InitFont() {
	this->font.loadFromFile("Fonts/DiabloHeavy.ttf");
}

void TextBox::Input(int charTyped) {
	if (charTyped != ENTER_KEY && charTyped != BACKSPACE_KEY)
		this->ssTextBox << static_cast<char>(charTyped);
	else if (charTyped == BACKSPACE_KEY) {
		if (this->ssTextBox.str().length() > 0)
			this->DeleteLastChar();
	}
	this->textBox.setString(ssTextBox.str() + "_");
}

void TextBox::DeleteLastChar() {
	string text = this->ssTextBox.str();
	string newText = "";

	for (int i = 0; i < text.length() - 1; i++)
		newText += text[i];

	this->ssTextBox.str("");
	this->ssTextBox << newText;

	this->textBox.setString(ssTextBox.str());
}

TextBox::TextBox() {
	this->limit = 9;
	this->InitFont();
	this->textBox.setFont(font);
	this->textBox.setPosition(WIN_WIDTH / 3, 500);
	this->textBox.setCharacterSize(55);
	this->textBox.setOutlineColor(Color::Black);
	this->textBox.setOutlineThickness(5);
	this->textBox.setFillColor(Color(159, 5, 0));
	this->textBox.setString("_");
}

string TextBox::GetTextBox() {
	return this->ssTextBox.str();
}

void TextBox::ResetTextBox() {
	this->ssTextBox.str() = "";
	this->textBox.setString(ssTextBox.str());
}

void TextBox::Update(Event& evnt) {
	int charTyped = evnt.text.unicode;
	if (charTyped < 128) {
		if (this->ssTextBox.str().length() <= this->limit)
			this->Input(charTyped);
		else if (this->ssTextBox.str().length() > this->limit && charTyped == BACKSPACE_KEY)
			this->DeleteLastChar();
	}
}

void TextBox::RenderTextBox(RenderWindow& window) {
	window.draw(this->textBox);
}