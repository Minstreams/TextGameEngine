#pragma once
//剧本元素，文本或选项
class TextUnit abstract
{
public:
	TextUnit *next;
	//核心剧本演出代码
	void virtual OnPerform() abstract;
	TextUnit();
	virtual ~TextUnit();
};

