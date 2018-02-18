#include "stdafx.h"
#include "GameSystem.h"


//启动游戏
void GameSystem::Launch()
{
	Init();
	LoadTextWorld();
	Perform();
	std::cout << "\n游戏结束";
	_getch();
	exit(0);
}

//读取设置
void GameSystem::Init()
{
	//读取setting
	setting = Setting{ 50,30 ,50 };

	system("title 岷溪的文字游戏引擎V0.01");
	system(("mode con cols=" + std::to_string(setting.columns) + " lines=" + std::to_string(setting.lines)).c_str());
}

//加载数据
void GameSystem::LoadTextWorld()
{
	loader.LoadText(world, std::string("data"));
}

//开始游戏演出
void GameSystem::Perform()
{
	//初始化
	textUnitStack.push(world.scenes.front()->root);

	//循环演出
	while (!gameOver) {
		//栈顶指针流动
		TextUnit *currentUnit = textUnitStack.top();
		textUnitStack.top() = currentUnit->next;

		currentUnit->OnPerform();

		while (textUnitStack.top() == nullptr) {
			//若演出结束则弹栈（进入选项分支时入栈）
			textUnitStack.pop();
			if (textUnitStack.empty()) {
				//若栈为空则演出完毕，结束游戏
				GameOver();
				return;
			}
		}
	}
}

//游戏结束
void GameSystem::GameOver()
{
	gameOver = true;
}

GameSystem::GameSystem()
{
	if (systemInstance != nullptr) {
		Error("游戏系统不唯一！冲突！");
		return;
	}
	systemInstance = this;

	currentPath = new CHAR[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentPath);
}


GameSystem::~GameSystem()
{
	delete currentPath;
}

GameSystem* GameSystem::systemInstance = nullptr;