#pragma once
///Ԥ����ͷ�ļ�

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <conio.h>
#include <Windows.h>


//��max���ո������һ�дﵽ�����һ�е�Ч��
inline void ClearLine(size_t maxLength) {
	std::cout << "\r" + std::string(maxLength, ' ') + "\r";
}