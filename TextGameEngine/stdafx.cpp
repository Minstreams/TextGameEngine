#include "stdafx.h"

void Error(const char * message)
{
	MessageBox(NULL, message, "剧本读取时出现问题!", MB_ICONEXCLAMATION);
	//TODO 打开文件
	exit(1);
}

void Error(const std::string & message)
{
	Error(message.c_str());
}

//用max个空格填充这一行达到清除这一行的效果
inline void ClearLine(size_t maxLength) {
	std::cout << "\r" + std::string(maxLength, ' ') + "\r";
}
