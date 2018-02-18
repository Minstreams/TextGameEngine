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

//设置光标隐藏或显示
void CommandController::SetCursorVisible(bool visible) {
	CursorInfo.bVisible = visible;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

//设置输出颜色
//   0 = 黑色      8 = 灰色
//   1 = 蓝色      9 = 淡蓝色
//   2 = 绿色      A = 淡绿色
//   3 = 浅绿色    B = 淡浅绿色
//   4 = 红色      C = 淡红色
//   5 = 紫色      D = 淡紫色
//   6 = 黄色      E = 淡黄色
//   7 = 白色      F = 亮白色
void CommandController::SetConsoleColor(WORD color)
{
	SetConsoleTextAttribute(handle, color);
}
