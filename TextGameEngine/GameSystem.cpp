#include "stdafx.h"
#include "GameSystem.h"


//������Ϸ
void GameSystem::Launch()
{
	Init();
	LoadTextWorld();
	Perform();
	std::cout << "\n��Ϸ����";
	_getch();
	exit(0);
}

//��ȡ����
void GameSystem::Init()
{
	//��ȡsetting
	setting = Setting{ 50,30 ,50 };

	system("title �Ϫ��������Ϸ����V0.01");
	system(("mode con cols=" + std::to_string(setting.columns) + " lines=" + std::to_string(setting.lines)).c_str());
}

//��������
void GameSystem::LoadTextWorld()
{
	loader.LoadText(world, std::string("data"));
}

//��ʼ��Ϸ�ݳ�
void GameSystem::Perform()
{
	//��ʼ��
	textUnitStack.push(world.scenes.front()->root);

	//ѭ���ݳ�
	while (!gameOver) {
		//ջ��ָ������
		TextUnit *currentUnit = textUnitStack.top();
		textUnitStack.top() = currentUnit->next;

		currentUnit->OnPerform();

		while (textUnitStack.top() == nullptr) {
			//���ݳ�������ջ������ѡ���֧ʱ��ջ��
			textUnitStack.pop();
			if (textUnitStack.empty()) {
				//��ջΪ�����ݳ���ϣ�������Ϸ
				GameOver();
				return;
			}
		}
	}
}

//��Ϸ����
void GameSystem::GameOver()
{
	gameOver = true;
}

GameSystem::GameSystem()
{
	if (systemInstance != nullptr) {
		Error("��Ϸϵͳ��Ψһ����ͻ��");
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