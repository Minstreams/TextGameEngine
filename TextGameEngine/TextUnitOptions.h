#pragma once
#include "TextUnit.h"

//ѡ�Ԫ
class TextUnitOptions :
	public TextUnit
{
public:
	//ѡ��ṹ��
	struct Option
	{
		std::string text;
		TextUnit *ptr;
	};
	//ѡ��
	std::vector<Option> options;
	void OnPerform() override;
	~TextUnitOptions();
};

