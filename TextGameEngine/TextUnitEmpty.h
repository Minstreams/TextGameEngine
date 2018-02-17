#pragma once
#include "TextUnit.h"
//空行单元
class TextUnitEmpty :
	public TextUnit
{
public:
	// 通过 TextUnit 继承
	virtual void OnPerform() override;
};

