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
	size_t choice = 0;//��ǰѡ��
	bool over = false;//����ָʾ

	while (!over) {
		size_t charPtr = 0;

		std::string choiceString = options.at(choice).text;

		bool inputed = false;//�Ƿ�������ϣ�
		bool back = false;	//�Ƿ��˸�
		while (!inputed) {

			//ȷ������
			switch (_getch())
			{
			case 13:
				//�س�
				inputed = true;
				break;
			case 8:
				//�˸�
				ClearLine(choiceString.size());
				charPtr = 0;
				choice++;
				if (choice >= options.size()) {
					choice -= options.size();
				}
				inputed = true;
				back = true;
				break;
			default:
				//���������
				std::cout << choiceString.at(charPtr);
				std::cout << choiceString.at(charPtr + 1);
				charPtr += 2;
				if (charPtr >= choiceString.size() - 1) {
					inputed = true;
				}
				break;
			}
		}

		//ѡ�����
		if (!back) {
			ClearLine(choiceString.size());
			std::cout << choiceString;

			//ȷ������
			bool check = false;
			while (!check) {
				switch (_getch())
				{
				case 13:
					//�س�
					check = true;
					over = true;
					break;
				case 8:
					//�˸�
					check = true;
					ClearLine(choiceString.size());
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
	}
	std::cout << std::endl;
	GameSystem::textUnitStack.push(options.at(choice).ptr);
}
