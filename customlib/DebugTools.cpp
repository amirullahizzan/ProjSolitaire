#include "DebugTools.h"

void DisplayCross()
{
	DrawLine(WINDOW_W_HALF,0, WINDOW_W_HALF,WINDOW_H,YELLOW,1);
	DrawLine(0, WINDOW_H_HALF, WINDOW_W, WINDOW_H_HALF,YELLOW,1);
}

void PrintfdxFast(int& _integer, float& _float)
{
	if (!_integer) { return; }
	printfDx("%d", _integer);
	if (!_float) { return; }
	printfDx("%f", _float);
}
