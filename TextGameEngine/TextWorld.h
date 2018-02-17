#pragma once
#include "TextScene.h"
//作为一整个剧本的类
class TextWorld
{
public:
	std::vector<TextScene*> scenes;

	TextWorld();
	~TextWorld();
};

