#include "stdafx.h"
#include "GameSystem.h"
#include "TextUnitSceneChange.h"

void TextUnitSceneChange::OnPerform()
{
	while (!GameSystem::systemInstance->textUnitStack.empty()) {
		GameSystem::systemInstance->textUnitStack.pop();
	}
	GameSystem::systemInstance->textUnitStack.push(sceneRoot);
}
