#pragma once

//�������װһЩ����̨���Ʒ���
class CommandController
{
private:
	HANDLE handle;	//����̨���
	CONSOLE_CURSOR_INFO CursorInfo;	//�����Ϣ
public:
	CommandController();
	~CommandController();

	//���ù�����ػ���ʾ
	void SetCursorVisible(bool visible);
	//���������ɫ
	//   0 = ��ɫ      8 = ��ɫ
	//   1 = ��ɫ      9 = ����ɫ
	//   2 = ��ɫ      A = ����ɫ
	//   3 = ǳ��ɫ    B = ��ǳ��ɫ
	//   4 = ��ɫ      C = ����ɫ
	//   5 = ��ɫ      D = ����ɫ
	//   6 = ��ɫ      E = ����ɫ
	//   7 = ��ɫ      F = ����ɫ
	void SetConsoleColor(WORD color);
};

