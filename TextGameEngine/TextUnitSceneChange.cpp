#include "stdafx.h"
#include "GameSystem.h"
#include "TextUnitSceneChange.h"

void TextUnitSceneChange::OnPerform()
{
	GameSystem::textUnitStack.top() = sceneRoot;
}
