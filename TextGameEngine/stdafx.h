#pragma once
///预编译头文件

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <conio.h>
#include <Windows.h>

#define SCRIPT_EXTENSION ".mts"	//脚本后缀名
//报错
extern void Error(const char* message);

//报错
extern void Error(const std::string & message);

//用max个空格填充这一行达到清除这一行的效果
extern inline void ClearLine(size_t maxLength);

//游戏设置
struct Setting {
	//屏幕设置
	size_t columns;
	size_t lines;

	//演出设置
	size_t textOutputInterval;//文本演出时，字与字之间间隔毫秒数
	WORD defaultBackgroundColor;
	WORD defaultTextColor;
};