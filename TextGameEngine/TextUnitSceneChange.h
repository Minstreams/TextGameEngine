#pragma once
#include "TextUnit.h"
//����ת����Ԫ
class TextUnitSceneChange :
	public TextUnit
{
public:
	TextUnit* sceneRoot;
	// ͨ�� TextUnit �̳�
	void OnPerform() override;
};

