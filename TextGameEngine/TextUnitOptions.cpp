#include "stdafx.h"
#include "GameSystem.h"
#include "TextUnitOptions.h"

TextUnitOptions::~TextUnitOptions()
{
	for each (Option option in options)
	{
		if (option.ptr != nullptr)delete option.ptr;
	}
}

void TextUnitOptions::OnPerform()
{
	size_t choice = 0;//当前选择
	bool over = false;//结束指示
	std::string choiceString;
	while (!over) {
		GameSystem::systemInstance->cmdController.SetConsoleColor(0x08);
		GameSystem::systemInstance->cmdController.SetCursorVisible(true);
		ClearLine(choiceString.size());

		size_t charPtr = 0;

		choiceString = options.at(choice).text;

		bool inputed = false;//是否输入完毕？
		bool back = false;	//是否退格？
		while (!inputed) {

			//确认输入
			switch (_getch())
			{
			case 13:
				//回车
				inputed = true;
				break;
			case 8:
				//退格
				charPtr = 0;
				choice++;
				if (choice >= options.size()) {
					choice -= options.size();
				}
				inputed = true;
				back = true;
				break;
			default:
				//其他任意键
				std::cout << choiceString.at(charPtr);
				std::cout << choiceString.at(charPtr + 1);
				charPtr += 2;
				if (charPtr >= choiceString.size() - 1) {
					inputed = true;
				}
				break;
			}
		}

		//选择完毕
		if (!back) {
			ClearLine(choiceString.size());
			GameSystem::systemInstance->cmdController.SetConsoleColor(0x80);
			GameSystem::systemInstance->cmdController.SetCursorVisible(false);
			std::cout << choiceString;

			//确认输入
			bool check = false;
			while (!check) {
				switch (_getch())
				{
				case 13:
					//回车
					check = true;
					over = true;
					break;
				case 8:
					//退格
					check = true;
					choice++;
					if (choice >= options.size()) {
						choice -= options.size();
					}
					break;
				default:
					break;
				}
			}
		}
		charPtr = 0;
	}
	GameSystem::systemInstance->cmdController.SetConsoleColor(0x07);
	std::cout << std::endl;
	GameSystem::systemInstance->textUnitStack.push(options.at(choice).ptr);
}
