#pragma once
#include "TextWorld.h"
//剧本加载器
class TextLoader
{
private:
	std::stack<TextUnit*> unitPtrStack;	//剧本单元指针栈
	std::string lineBuffer;		//行缓冲
	std::string fileName;		//文件名
	//报错
	void Error(const char* message);
	//报错
	void Error(const std::string & message);
	//添加下一个单元
	inline void AddNext(TextUnit* newUnit);
public:
	//加载剧本
	void LoadText(TextWorld &world);
	
};

