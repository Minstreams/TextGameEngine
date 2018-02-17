#include "stdafx.h"
#include "TextWorld.h"


TextWorld::TextWorld()
{
}


TextWorld::~TextWorld()
{
	for each (TextScene* sceneRoot in scenes)
	{
		delete sceneRoot;
		sceneRoot = nullptr;
	}
}
