#pragma once
#include "TextWorld.h"
//�籾������
class TextLoader
{
private:
	std::stack<TextUnit*> unitPtrStack;	//�籾��Ԫָ��ջ
	std::string lineBuffer;		//�л���
	std::string fileName;		//�ļ���
	//����
	void Error(const char* message);
	//����
	void Error(const std::string & message);
	//�����һ����Ԫ
	inline void AddNext(TextUnit* newUnit);
public:
	//���ؾ籾
	void LoadText(TextWorld &world);
	
};

