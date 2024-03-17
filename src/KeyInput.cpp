// �L�[���͊Ǘ�
#include "KeyInput.h"

#define MAX_KEY_NUM 256

static unsigned char gKey[MAX_KEY_NUM];
int MouseLeftFrame;
int MouseRightFrame;

static bool IsOverKeyNum(int key_id);	// �z��̌��ؗp

// ������
void KeyInputInit()
{
	for (int i = 0; i < MAX_KEY_NUM; ++i) {
		gKey[i] = 0;
	}
}
// �X�V
int KeyInputUpdate()
{
	char tmp_key[MAX_KEY_NUM];
	GetHitKeyStateAll(tmp_key);

	for (int i = 0; i < MAX_KEY_NUM; ++i) {
		if (tmp_key[i] != 0) {
			gKey[i]++;
			if (gKey[i] >= UCHAR_MAX)	gKey[i] = UCHAR_MAX;
		}
		else {
			gKey[i] = 0;
		}
	}
	return 0;
}
// �I��
void KeyInputExit()
{
	;
}

// ����L�[��1�񂾂���������
bool GetKeyPush(int key_id)
{
	if (IsOverKeyNum(key_id)) return false;
	return (gKey[key_id] == 1);
}
bool GetKeyDown(int key_id)
{
	if (IsOverKeyNum(key_id)) return false;
	return (gKey[key_id] == 1);
}

// ����L�[�̉������
bool GetKeyRelease(int key_id)
{
	if (IsOverKeyNum(key_id)) return false;
	return (gKey[key_id] == 0);
}
// ����L�[�̒���������
bool GetKeyRepeat(int key_id)
{
	if (IsOverKeyNum(key_id)) return false;
	return (gKey[key_id] > 1);
}
// gKey�z�񌟏ؗp
bool IsOverKeyNum(int key_id)
{
	return (key_id >= MAX_KEY_NUM) || (key_id < 0);
}

bool GetAnyMouseInput(int mouse_id)
{
	return GetMouseInput() && mouse_id != 0;
}

bool GetAnyMouseClick(int mouse_id)
{
	return GetAnyMouseInput(mouse_id);
}

bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button) {
		return true;
	}
	return false;
}

bool PushMouseInput(int button)
{
	if (button & MOUSE_INPUT_LEFT) {
		if (MouseLeftFrame == 1) {
			return true;
		}
	}
	if (button & MOUSE_INPUT_RIGHT) {
		if (MouseRightFrame == 1) {
			return true;
		}
	}
	return false;
}

bool HoldMouseInput(int button)
{
	if (GetMouseInput() & button)
	{
		return true;
	}
	return false;
}

bool OnReleaseMouseInput(int button)
{
	if (button & MOUSE_INPUT_LEFT)
	{
		if (MouseLeftFrame == 0 && (GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
		{
			return true;
		}
	}
	if (button & MOUSE_INPUT_RIGHT)
	{
		if (MouseRightFrame == 0 && (GetMouseInput() & MOUSE_INPUT_RIGHT) == 0)
		{
			return true;
		}
	}
	return false;
}