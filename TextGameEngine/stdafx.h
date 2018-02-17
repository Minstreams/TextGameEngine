#pragma once
///预编译头文件

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <conio.h>
#include <Windows.h>


//用max个空格填充这一行达到清除这一行的效果
inline void ClearLine(size_t maxLength) {
	std::cout << "\r" + std::string(maxLength, ' ') + "\r";
}