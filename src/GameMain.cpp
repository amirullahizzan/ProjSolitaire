#include "WinMain.h"
#include "../customlib/Pos.h"
#include "../customlib/DebugTools.h"
#include "../customsrc/Scene.h"
#include "../customsrc/PlayingCards.h"

extern Scene* currentScene_p;

struct Column
{

};

struct Deck
{

};



void GameInit()
{
	//currentScene_p = new MainMenuScene();
	currentScene_p = new GameScene();
}

void GameUpdate()
{
	currentScene_p->Update();
}

void GameDraw()
{
	currentScene_p->Render();
	DisplayCross();
	
}

void GameExit()
{


}