#include "stdafx.h"
#include "GameSystem.h"
#include "TextUnitString.h"

void TextUnitString::OnPerform()
{
	bool skip = false;

	GameSystem::systemInstance->cmdController.SetCursorVisible(true);

	for (size_t i = 0;i < text.size();i++) {
		if (text.at(i) == '#')break;

		std::cout << text.at(i);


		if (_kbhit() && (_getch() == 13)) skip = true;	//演出中途按回车跳过
		if (!skip) Sleep(GameSystem::systemInstance->setting.textOutputInterval);
	}
	GameSystem::systemInstance->cmdController.SetCursorVisible(false);
	std::cout << std::endl;
	_getch();
}

TextUnitString::TextUnitString(std::string & text) :text(text)
{
}