#pragma once
#include "TextUnit.h"

//�ı���Ԫ
class TextUnitString :
	public TextUnit
{
private:
	std::string text;
	void OnPerform()override;
public:
	TextUnitString(std::string &text);
};

