#include "stdafx.h"
#include "TextScene.h"



TextScene::TextScene(std::string &name) :name(name), root(nullptr)
{
}

TextScene::~TextScene()
{
	if (root != nullptr) {
		delete root;
		root = nullptr;
	}
}
