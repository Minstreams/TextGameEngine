#pragma once
///Ԥ����ͷ�ļ�

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <conio.h>
#include <Windows.h>

#define SCRIPT_EXTENSION ".mts"	//�ű���׺��
//����
extern void Error(const char* message);

//����
extern void Error(const std::string & message);

//��max���ո������һ�дﵽ�����һ�е�Ч��
extern inline void ClearLine(size_t maxLength);

//��Ϸ����
struct Setting {
	//��Ļ����
	size_t columns;
	size_t lines;

	//�ݳ�����
	size_t textOutputInterval;//�ı��ݳ�ʱ��������֮����������
	WORD defaultBackgroundColor;
	WORD defaultTextColor;
};