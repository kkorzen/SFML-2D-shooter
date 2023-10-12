#pragma once
#include "Globals.h"

class Score {
private:
	int scoreNumber = 0;
	ostringstream ssScore;

	Font font;
	Text score;

	void InitFont();
	void InitScore();
	
public:
	Score();
	~Score() = default;

	int GetScore();

	void ScoreUp();
	void ResetScore();

	void Render(RenderWindow& window);
	
};