#include "BestPlayers.h"

void BestPlayers::InitFont() {
	this->font.loadFromFile("Fonts/DiabloHeavy.ttf");
}

void BestPlayers::InitTexture() {
	this->texture.loadFromFile("Sprites/BestPlayersPic.jpg");
}

void BestPlayers::InitSprite() {
	this->sprite.setTexture(texture);
}

void BestPlayers::InitEasyRecs() {
	for (int i = 0; i < 10; i++) {
		this->easyRec[i].setFont(font);
		this->easyRec[i].setCharacterSize(30);
		this->easyRec[i].setFillColor(Color(159, 5, 0));
		this->easyRec[i].setOutlineColor(Color::Black);
		this->easyRec[i].setOutlineThickness(5.f);
		this->easyRec[i].setPosition(WIN_WIDTH / 25, 275 + 40 * i);	
	}
}

void BestPlayers::InitNormalRecs() {
	for (int i = 0; i < 10; i++) {
		this->normalRec[i].setFont(font);
		this->normalRec[i].setCharacterSize(30);
		this->normalRec[i].setFillColor(Color(159, 5, 0));
		this->normalRec[i].setOutlineColor(Color::Black);
		this->normalRec[i].setOutlineThickness(5.f);
		this->normalRec[i].setPosition(WIN_WIDTH / 2.8, 275 + 40 * i);
	}
}

void BestPlayers::InitInsaneRecs() {
	for (int i = 0; i < 10; i++) {
		this->insaneRec[i].setFont(font);
		this->insaneRec[i].setCharacterSize(30);
		this->insaneRec[i].setFillColor(Color(159, 5, 0));
		this->insaneRec[i].setOutlineColor(Color::Black);
		this->insaneRec[i].setOutlineThickness(5.f);
		this->insaneRec[i].setPosition(WIN_WIDTH / 1.4, 275 + 40 * i);
	}
}

void BestPlayers::InitTextRecs() {
	this->InitEasyRecs();
	this->InitNormalRecs();
	this->InitInsaneRecs();
}

void BestPlayers::Sort(Record* rec) {
	for (size_t i = 0; i < 30; i++) {
		for (size_t j = i + 1; j < 30; j++) {
			if (rec[j].userScore > rec[i].userScore) {
				Record tmp = rec[i];
				rec[i] = rec[j];
				rec[j] = tmp;
			}
		}
	}
}

void BestPlayers::SaveToFile(TextBox& tb, Difficulty& diff, Score& score) {
	//this->save.open("BestPlayers.txt", fstream::app);
	this->file << diff.diffSelectedFlag << endl;
	this->file << tb.GetTextBox() << endl;
	this->file << score.GetScore() << endl;
	//this->save.close();
}

void BestPlayers::LoadFromFile() {
	//this->read.open("BestPlayers.txt");
	if(this->file.good()) {
		while (getline(this->file, this->line)) {
			if (this->lineNumber == this->i+1)
				this->recs[this->j].difficulty = atoi(this->line.c_str());
			else if (this->lineNumber == this->i + 2)
				this->recs[this->j].userName = this->line;
			else if (this->lineNumber == this->i + 3)
				this->recs[this->j].userScore = atoi(this->line.c_str());

			if (this->lineNumber % 3 == 0) {
				this->i += 3; this->j++;
			}
			this->lineNumber++;
		}
		this->file.clear();
		this->file.seekg(0, fstream::beg);
		//this->read.close();
	}
}

BestPlayers::BestPlayers() {
	this->InitTexture();
	this->InitSprite();
	this->InitFont();
	this->InitTextRecs();
}

void BestPlayers::ResetIterators() {
	this->ei = 0;
	this->ni = 0;
	this->ii = 0;
	this->i = 0;
	this->j = 0;
}

void BestPlayers::UpdateSaving(TextBox& tb, Difficulty& diff, Score& score) {
	SaveToFile(tb, diff, score);
}

void BestPlayers::UpdateReading() {
	this->LoadFromFile();
}

void BestPlayers::OpenFile() {
	this->file.open("BestPlayers.txt", fstream::in | fstream::out | fstream::app);
}

void BestPlayers::CloseFile() {
	this->file.close();
}

void BestPlayers::Update() {
	for (int i = 0; i < 30; i++) {
		if (this->recs[i].difficulty == 1) {
			this->eRecs[this->ei] = this->recs[i];
			this->eRecs[this->ei] = this->recs[i];
			this->ei++;
		}
		else if (this->recs[i].difficulty == 2) {
			this->nRecs[this->ni] = this->recs[i];
			this->nRecs[this->ni] = this->recs[i];
			this->ni++;
		}
		else if (this->recs[i].difficulty == 3) {
			this->iRecs[this->ii] = this->recs[i];
			this->iRecs[this->ii] = this->recs[i];
			this->ii++;
		}
		else 0;
	}

	this->ResetIterators();

	this->Sort(this->eRecs);
	this->Sort(this->nRecs);
	this->Sort(this->iRecs);

	for (int i = 0; i < 10; i++)
		this->easyRec[i].setString(to_string(i + 1) + ". " + this->eRecs[i].userName + " - " + to_string(this->eRecs[i].userScore));
	for (int i = 0; i < 10; i++)
		this->normalRec[i].setString(to_string(i + 1) + ". " + this->nRecs[i].userName + " - " + to_string(this->nRecs[i].userScore));
	for (int i = 0; i < 10; i++)
		this->insaneRec[i].setString(to_string(i + 1) + ". " + this->iRecs[i].userName + " - " + to_string(this->iRecs[i].userScore));
}

void BestPlayers::RenderAll(RenderWindow& window) {
	this->Render(window);
	for (int i = 0; i < 10; i++) {
		window.draw(this->easyRec[i]);
		window.draw(this->normalRec[i]);
		window.draw(this->insaneRec[i]);
	}
}