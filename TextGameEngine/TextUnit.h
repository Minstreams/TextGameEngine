#pragma once
//�籾Ԫ�أ��ı���ѡ��
class TextUnit abstract
{
public:
	TextUnit *next;
	//���ľ籾�ݳ�����
	void virtual OnPerform() abstract;
	TextUnit();
	virtual ~TextUnit();
};

