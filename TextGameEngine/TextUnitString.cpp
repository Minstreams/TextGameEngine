#include "stdafx.h"
#include "TextUnitString.h"

void TextUnitString::OnPerform()
{
	bool skip = false;
	for (size_t i = 0;i < text.size();i++) {
		if (text.at(i) == '#')break;
		std::cout << text.at(i);
		if (_kbhit()) skip = true;
		if (!skip) Sleep(50);
	}
	std::cout << std::endl;
	_getch();
}

TextUnitString::TextUnitString(std::string & text) :text(text)
{
}