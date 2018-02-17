#include "stdafx.h"
#include "GameSystem.h"
#include "TextUnitSceneChange.h"

void TextUnitSceneChange::OnPerform()
{
	while (!GameSystem::textUnitStack.empty()) {
		GameSystem::textUnitStack.pop();
	}
	GameSystem::textUnitStack.push(sceneRoot);
}
