// �L�[���͊Ǘ�
#pragma once
#include "WinMain.h"

void KeyInputInit();			// ������
int KeyInputUpdate();			// �X�V
void KeyInputExit();			// �I��


bool GetKeyPush(int key_id);		// 1�񂾂�
bool GetKeyDown(int key_id);		// 1�񂾂�
bool GetKeyRelease(int key_id);	// �����ꂽ
bool GetKeyRepeat(int key_id);	// 2��ȏ�(������)



