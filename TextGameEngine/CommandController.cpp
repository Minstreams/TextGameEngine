#include "stdafx.h"
#include "CommandController.h"



CommandController::CommandController()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(handle, &CursorInfo);  
}


CommandController::~CommandController()
{
}

//���ù�����ػ���ʾ
void CommandController::SetCursorVisible(bool visible) {
	CursorInfo.bVisible = visible;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

//���������ɫ
//   0 = ��ɫ      8 = ��ɫ
//   1 = ��ɫ      9 = ����ɫ
//   2 = ��ɫ      A = ����ɫ
//   3 = ǳ��ɫ    B = ��ǳ��ɫ
//   4 = ��ɫ      C = ����ɫ
//   5 = ��ɫ      D = ����ɫ
//   6 = ��ɫ      E = ����ɫ
//   7 = ��ɫ      F = ����ɫ
void CommandController::SetConsoleColor(WORD color)
{
	SetConsoleTextAttribute(handle, color);
}
