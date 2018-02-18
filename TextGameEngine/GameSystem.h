#pragma once
#include "TextLoader.h"
#include "CommandController.h"

//游戏系统
class GameSystem
{
private:
	///对象
	TextWorld world;	//存储剧本数据
	TextLoader loader;	//剧本加载器

	bool gameOver = false;

public:
	static GameSystem* systemInstance;	//系统单例

	bool pause = false;	//暂停状态变量
	std::stack<TextUnit*> textUnitStack;	//剧本元素栈，控制流程
	Setting setting;	//各种游戏设置
	CommandController cmdController;	//控制台控制器

	LPSTR currentPath;	//当前文件目录
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

