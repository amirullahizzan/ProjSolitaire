#include "TextEffect.h"

std::string GetTimedCharacter(const std::string& _string, int _timer, int& _s_tick, int& _s_characterIndex)
{
	std::string perCharacter = _string.substr(0, _s_characterIndex);
	if (_s_tick > _timer)
	{
		_s_characterIndex++;
		_s_tick = 0;
	}
	_s_tick++;
	return perCharacter;
}

void ResetTimedCharacter(int& _s_tick, int& _s_characterIndex)
{
		_s_tick = 0;
		_s_characterIndex = 0;
}

const int GetTextSize(const std::string& _string)
{
	return GetDrawStringWidth((_string.c_str())	, 
		static_cast<int>(_string.length())) 
		* 0.5f;
}


//DrawString(WINDOW_W_HALF, WINDOW_H_HALF, _string.substr(0, _characterIndex).c_str(), YELLOW);
//DrawString(WINDOW_W_HALF - fontsize, WINDOW_H_HALF + buttonUIOffset * i, text[i].substr(0, characterIndex).c_str(), YELLOW);