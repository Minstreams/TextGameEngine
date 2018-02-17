#pragma once
#include "TextUnit.h"
//一个剧本场景
class TextScene
{
public:
	std::string name;
	TextUnit *root;
	TextScene(std::string &name);
	~TextScene();
};

