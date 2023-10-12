#pragma once
#include "Globals.h"
#include "Entity.h"
#include "TextBox.h"
#include "GameState.h"

typedef struct {
	unsigned short difficulty;
	string userName;
	unsigned short userScore;
}Record;

class BestPlayers :public Entity{
private:

	//Record recs[30];

	string line;
	unsigned short lineNumber = 1;

	/*Record recs[30];
	Record eRecs[30];
	Record nRecs[30];
	Record iRecs[30];*/

	short ei =0; // iterator for eRecs
	short ni =0; // iterator for nRecs
	short ii =0; // iterator for iRecs
	short i = 0;
	short j = 0;

	fstream file;
	//ofstream save;
	//ifstream read;

	//FILE* file;

	Font font;
	Text easyRec[10];
	Text normalRec[10];
	Text insaneRec[10];

	void InitFont();
	void InitTexture();
	void InitSprite();
	void InitEasyRecs();
	void InitNormalRecs();
	void InitInsaneRecs();
	void InitTextRecs();

	void Sort(Record* rec);

	void SaveToFile(TextBox& tb, Difficulty& diff, Score& score);
	void LoadFromFile();

public:
	Record recs[30];
	Record eRecs[30];
	Record nRecs[30];
	Record iRecs[30];

	BestPlayers();
	~BestPlayers() = default;

	void ResetIterators();

	void UpdateSaving(TextBox& tb, Difficulty& diff, Score& score);
	void UpdateReading();

	void OpenFile();
	void CloseFile();

	void Update();

	void RenderAll(RenderWindow& window);
};