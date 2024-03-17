#include "WinMain.h"
#define DEBUG

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetWindowSize(WINDOW_W, WINDOW_H);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	SetBackgroundColor(0, 180, 0);
	SetMainWindowText("Solitaire");
	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);


	SRand((int)time(NULL));

	KeyInputInit();
	PadInputInit();
	MouseInputInit();
	GameInit();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		KeyInputUpdate();
		PadInputUpdate();
		MouseInputUpdate();
		GameUpdate();

		ClearDrawScreen();
#ifdef DEBUG
		clsDx();
#endif

		GameDraw();
		ScreenFlip();
	}



	GameExit();

	DxLib_End();

	return 0;
}