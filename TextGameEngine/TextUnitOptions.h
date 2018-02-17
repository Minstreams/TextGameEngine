#pragma once
#include "TextUnit.h"

//选项单元
class TextUnitOptions :
	public TextUnit
{
public:
	//选项结构体
	struct Option
	{
		std::string text;
		TextUnit *ptr;
	};
	//选项
	std::vector<Option> options;
	void OnPerform() override;
	~TextUnitOptions();
};

