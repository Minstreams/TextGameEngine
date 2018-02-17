#include "TextUnit.h"

TextUnit::TextUnit() :next(nullptr)
{
}

TextUnit::~TextUnit()
{
	if (next != nullptr) {
		delete next;
		next = nullptr;
	}
}
