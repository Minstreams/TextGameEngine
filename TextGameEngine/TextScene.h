#pragma once
#include "TextUnit.h"
//һ���籾����
class TextScene
{
public:
	std::string name;
	TextUnit *root;
	TextScene(std::string &name);
	~TextScene();
};

