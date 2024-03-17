#pragma once
#include "../src/WinMain.h"
#include "../customlib/Pos.h"

#define MAX_CARDS_INGAME 104 
#define INITIAL_CARDS_ON_TABLE 54

struct PlayingCards
{
	Pos pointPos_ = { WINDOW_W_HALF,WINDOW_H_HALF };
	
	int face_imageHandler = -1;
	int back_imageHandler = -1;
	bool isDrawn = false;
	bool isFaceUp = false;
	int hitboxRadian = 42;

	//std::vector< PlayingCards* , tableCards[52 - hands only]>; //Early face up = 0;

	PlayingCards();

	enum ESuit
	{
		NOSUIT = -1,
		Hearts, Diamonds, Clubs, Spades
	};
	ESuit suitType = NOSUIT;

	enum ERank
	{
		NORANK = -1,
		Ace = 1,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
	};
	ERank rankType = NORANK;

	Pos pos_;
	Pos pos2_;
	Pos size_;

	void Update();
	void Render();

	 Pos GetPos1() const;
	 Pos GetPos2() const;
	 Pos GetPointPos() const;

	void SetFaceUp();
	 void SetPointPos(Pos& pointpos_);
	bool isDragged = false;
	void SetSuit(ESuit _suitType);
	void SetRank(ERank _rankType);

private:

	void UpdateCards();
	void RenderFace(Pos& _pos, Pos& _pos2);
	void RenderBack(Pos& _pos, Pos& _pos2);
	void RenderCards(Pos& _pos, Pos& _pos2);
	void RenderShadow(Pos& _pos, Pos& _pos2);

};

void GenerateAllCards();