#pragma once
#pragma once
#include "../src/WinMain.h"
//#include "../customlib/Pos.h"
#include "../customlib/HitBox.h"
#include "../customlib/TextEffect.h"
#include "PlayingCards.h"
#include <random>

struct Scene
{
	bool isInit = false;
	virtual void Init();
	virtual void Update();
	virtual void Render();
protected:
	void InitOnceFlag();
};

struct MainMenuScene : public Scene
{
	MainMenuScene();
	std::vector<Scene> sceneList;

	void Update() override;
	void Render() override;


private:
	int textTickBuffer = 0;
	int charIndexBuffer = 0;
	void PlayerControl();
	void DisplayAnimatedTitle();
	void DisplayAnimatedMenuText();
	//void CarrouselObject();
};

struct GameScene : public Scene
{
	GameScene();
	std::array<PlayingCards*, MAX_CARDS_INGAME> playingCards_p = {};
	void Update() override;
	void Render() override;


private:
	bool onePairMode = true;
	const int numCompleteGroups = 8; // Number of finish groups in Spider Solitaire

	bool multiPairMode = false;

	void InitSet(std::array<PlayingCards*, MAX_CARDS_INGAME>& _playingCards_p);
	PlayingCards* draggedCard = nullptr;
	int deckLeft = MAX_CARDS_INGAME;
	int cardDrawnCounter = 0;

	static constexpr int MAX_COLUMN = 14;
	static constexpr int MAX_ROW = 10;
	const Pos UPPER_BORDER = { 50,200 };
	const Pos BORDER_OFFSET = { 50,100 };

	bool isDraggingCard = false;
	int back_imageHandler = -1;
	PlayingCards* Row[MAX_ROW][MAX_COLUMN] = {};
	//std::vector<std::vector<PlayingCards*>>	Row{std::vector<PlayingCards*>(MAX_ROW),std::vector<PlayingCards*>(MAX_COLUMN)};

	PlayingCards* Deck = {};
	Pos deckPointPos = {100,100};
	Pos deckButtonPos;
	Pos deckButtonPos2;
	Pos deckButtonSize;
	void InitShuffle(std::array<PlayingCards*, MAX_CARDS_INGAME>& _playingCards_p);
	void InitRows();
	void FaceUpLastRow();
	void SetDeck();
	void DrawBorderLine();
	void RenderDrawCardButton();
	bool IsMouseHitCard(Pos _cardPos1, Pos _cardPos2);
	void SetDragCard(PlayingCards* cardsIndex);
	void DragCard(PlayingCards* cardsIndex);
	bool CardHitCard(const Pos& pos1, const Pos& pos2, const Pos& otherPos1, const Pos& otherPos2);
	void SetCardChild(PlayingCards*& draggedCard, PlayingCards*& _otherCard);
	void DropCard(PlayingCards*& cardsIndex);
	void DrawCards();
	Pos initialPos = { 0,0 };

	Pos debugPos;
};

struct EndGameScene : public Scene
{
	void Update() override;
	void Render() override;
};

