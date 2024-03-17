#pragma once
#include "../src/WinMain.h"
#include <string>

std::string GetTimedCharacter(const std::string& _string, int _timer, int& _s_tick, int& _s_characterIndex);
void ResetTimedCharacter(int& _s_tick, int& _s_characterIndex);

const int GetTextSize(const std::string& _string);
