#pragma once
#include "Globals.h"

#define ENTER_KEY 27
#define BACKSPACE_KEY 8

class TextBox {
	friend class BestPlayer;
private:
	Text textBox;
	Font font;
	ostringstream ssTextBox;

	short limit;

	void InitFont();

	void Input(int charTyped);
	void DeleteLastChar();

public:
	TextBox();
	~TextBox() = default;

	string GetTextBox();
	void ResetTextBox();

	void Update(Event& evnt);
	void RenderTextBox(RenderWindow& window);
};