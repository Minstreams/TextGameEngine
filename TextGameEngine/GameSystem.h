#pragma once
#include "TextLoader.h"

//��Ϸϵͳ
class GameSystem
{
private:
	///����
	TextWorld world;	//�洢�籾����
	TextLoader loader;	//�籾������


	bool gameOver = false;


public:
	bool pause = false;	//��ͣ״̬����
	static std::stack<TextUnit*> textUnitStack;	//�籾Ԫ��ջ����������


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

