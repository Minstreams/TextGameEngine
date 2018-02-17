#pragma once
#include "TextUnit.h"

//文本单元
class TextUnitString :
	public TextUnit
{
private:
	std::string text;
	void OnPerform()override;
public:
	TextUnitString(std::string &text);
};

