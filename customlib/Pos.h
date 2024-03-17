#pragma once

struct Pos
{
	Pos()
	{
		x_ = 0;
		y_ = 0;
	}

	Pos(int _x, int _y)
	{
		x_ = _x;
		y_ = _y;
	}
	int x_, y_;
};