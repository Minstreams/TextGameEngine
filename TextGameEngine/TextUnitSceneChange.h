#pragma once
#include "TextUnit.h"
//场景转换单元
class TextUnitSceneChange :
	public TextUnit
{
public:
	TextUnit* sceneRoot;
	// 通过 TextUnit 继承
	void OnPerform() override;
};

