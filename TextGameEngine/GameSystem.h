#pragma once
#include "TextLoader.h"
#include "CommandController.h"

//��Ϸϵͳ
class GameSystem
{
private:
	///����
	TextWorld world;	//�洢�籾����
	TextLoader loader;	//�籾������

	bool gameOver = false;

public:
	static GameSystem* systemInstance;	//ϵͳ����

	bool pause = false;	//��ͣ״̬����
	std::stack<TextUnit*> textUnitStack;	//�籾Ԫ��ջ����������
	Setting setting;	//������Ϸ����
	CommandController cmdController;	//����̨������

	LPSTR currentPath;	//��ǰ�ļ�Ŀ¼
	//������Ϸ
	void Launch();
	//��ȡ����
	void Init();
	//��������
	void LoadTextWorld();
	//��ʼ��Ϸ�ݳ�
	void Perform();
	//��Ϸ����
	void GameOver();


	GameSystem();
	~GameSystem();
};

