#include "stdafx.h"

void Error(const char * message)
{
	MessageBox(NULL, message, "�籾��ȡʱ��������!", MB_ICONEXCLAMATION);
	//TODO ���ļ�
	exit(1);
}

void Error(const std::string & message)
{
	Error(message.c_str());
}

//��max���ո������һ�дﵽ�����һ�е�Ч��
inline void ClearLine(size_t maxLength) {
	std::cout << "\r" + std::string(maxLength, ' ') + "\r";
}
