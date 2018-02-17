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
	system("title �Ϫ��������Ϸ����V0.01");
	system("mode con cols=50 lines=30");
}

//��������
void GameSystem::LoadTextWorld()
{
	loader.LoadText(world);
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
}


GameSystem::~GameSystem()
{
}

std::stack<TextUnit*> GameSystem::textUnitStack = std::stack<TextUnit*>();