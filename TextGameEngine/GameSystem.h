#pragma once
#include "TextLoader.h"

//游戏系统
class GameSystem
{
private:
	///对象
	TextWorld world;	//存储剧本数据
	TextLoader loader;	//剧本加载器


	bool gameOver = false;


public:
	bool pause = false;	//暂停状态变量
	static std::stack<TextUnit*> textUnitStack;	//剧本元素栈，控制流程


	//启动游戏
	void Launch();
	//读取设置
	void Init();
	//加载数据
	void LoadTextWorld();
	//开始游戏演出
	void Perform();
	//游戏结束
	void GameOver();
	GameSystem();
	~GameSystem();
};

