#include "stdafx.h"
#include <fstream>
#include "TextLoader.h"

#include "TextUnitString.h"
#include "TextUnitOptions.h"
#include "TextUnitEmpty.h"
#include "TextUnitSceneChange.h"

struct recordSceneToChange {
	TextUnitSceneChange* changer;
	std::string sceneRoot;
};

void TextLoader::LoadText(TextWorld &world)
{
	std::ifstream fileStream;	//�ļ���
	fileStream.open("data.mts", std::ios::in);
	std::vector<recordSceneToChange> sceneChangeRecord;	//��¼Ҫת�������ĵط�
	std::stack<TextUnitOptions*> optionStack;	//ѡ�Ԫ����ջ
	optionStack.push(nullptr);


	//��ʼѭ��
	while (!fileStream.eof()) {
		///��ȡ����
		std::getline(fileStream, lineBuffer);
		bool optionStatus = false;	//��¼�Ƿ���ѡ��༭״̬
		///���в���
		//��һ��:ȥ����ͷ��\t
		size_t begin = 0;
		for (;begin < lineBuffer.size() && lineBuffer.at(begin) == '\t'; begin++) {}

		//�ڶ���,�ж�ָ������
		if (begin == lineBuffer.size()) {
			//�ǿ���
			if (unitPtrStack.empty() || optionStack.top() != nullptr || unitPtrStack.top() == nullptr) {
				continue;
			}
			AddNext(new TextUnitEmpty());
		}
		else if (lineBuffer.at(begin) == '#') {
			//��ע��
			continue;
		}
		else if (lineBuffer.at(begin) == '}') {
			//��ѡ�����ݵĽ���
			if (lineBuffer.substr(begin).size() != 1) {
				Error("}���治���ж���!\n\n��������:" + lineBuffer);
				return;
			}
			optionStack.pop();
			unitPtrStack.pop();
			continue;
		}
		else if (lineBuffer.at(begin) == '[') {
			//��ָ��
			size_t endSign = lineBuffer.find(']', begin);

			if (endSign == std::string::npos) {
				Error("�Ҳ�����Ӧ��]\n\n��������:" + lineBuffer);
				return;
			}

			//��ȡָ������
			std::string order = lineBuffer.substr(begin + 1, endSign - begin - 1);
			if (order.front() == '/') {
				if (order.size() == 2) {
					//����ѡ������
					size_t number = order.back() - '0';

					if (number < 0 || number>9) {
						Error("��Чָ��!\n\n��������:" + lineBuffer);
						return;
					}

					if (optionStack.top() == nullptr || optionStack.top()->options.size() <= number) {
						Error("û�ж�Ӧ��ѡ��!\n\n��������:" + lineBuffer);
						return;
					}

					if (optionStack.top()->options.at(number).ptr != nullptr) {
						Error("ѡ���Ѿ�������!\n\n��������:" + lineBuffer);
						return;
					}

					std::string orderMessage = lineBuffer.substr(endSign + 1);
					if (orderMessage.front() == '{') {
						if (orderMessage.size() != 1) {
							Error("{�������ڲ�֧�ּ��ϱ�Ķ���(��Ϊ������Ƚ���д),{��������ݻ�һ�а�!\n\n��������:" + lineBuffer);
							return;
						}
						unitPtrStack.push(new TextUnitEmpty());
						optionStack.top()->options.at(number).ptr = unitPtrStack.top();


						optionStack.push(nullptr);
					}
					else {
						optionStack.top()->options.at(number).ptr = new TextUnitString(orderMessage);
						optionStatus = true;
					}

				}
				else {
					//�����³���
					if (unitPtrStack.size() > 1) {
						Error("�����³�����ָ��ܳ���������!\n\n��������:" + lineBuffer);
						return;
					}

					std::string name = order.substr(1);

					for each (TextScene* sceneRoot in world.scenes)
					{
						int i = 0;
						if (sceneRoot->name._Equal(name)) {
							Error("������������!\n\n��������:" + lineBuffer);
							return;
						}
					}

					world.scenes.push_back(new TextScene(name));
					world.scenes.back()->root = new TextUnitEmpty();

					if (unitPtrStack.empty()) {
						unitPtrStack.push(world.scenes.back()->root);
					}
					else {
						unitPtrStack.top() = world.scenes.back()->root;
					}
				}
			}
			else {
				if (unitPtrStack.empty()) {
					Error("δָ������!\n\n��������:" + lineBuffer);
					return;
				}

				if (order.size() == 1) {
					//����ѡ��
					int number = order.back() - '0';

					if (number < 0 || number>9) {
						Error("��Чָ��!\n\n��������:" + lineBuffer);
						return;
					}

					std::string orderMessage = lineBuffer.substr(endSign + 1);
					if (number == 0) {
						//�����µ�ѡ�Ԫ
						optionStack.top() = new TextUnitOptions();
						AddNext(optionStack.top());
						optionStack.top()->options.push_back(TextUnitOptions::Option{ orderMessage ,nullptr });
					}
					else if (optionStack.top() == nullptr || number != optionStack.top()->options.size()) {
						Error("ѡ�����û�а���˳��!\n\n��������:" + lineBuffer);
						return;
					}
					else {
						optionStack.top()->options.push_back(TextUnitOptions::Option{ orderMessage ,nullptr });
					}

					optionStatus = true;
				}
				else if (order.find("to ") == 0) {
					//ת������
					TextUnitSceneChange* changer = new TextUnitSceneChange();
					sceneChangeRecord.push_back(recordSceneToChange{ changer, order.substr(3) });
					AddNext(changer);
					unitPtrStack.top() = nullptr;
				}
				else {
					Error("��Чָ��!\n\n��������:" + lineBuffer);
					return;
				}
			}
		}
		else {
			//���ı�
			if (unitPtrStack.empty()) {
				Error("�ı�����δָ������!\n\n��������:" + lineBuffer);
				return;
			}

			AddNext(new TextUnitString(lineBuffer.substr(begin)));
		}

		if (optionStack.top() != nullptr && !optionStatus) {
			//�������༭ѡ��,�����ѡ��ջ������
			optionStack.top() = nullptr;
		}
	}

	//�ӳٴ�����ת����Ϣ
	for each (recordSceneToChange record in sceneChangeRecord)
	{
		for each (TextScene* sceneRoot in world.scenes)
		{
			if (sceneRoot->name._Equal(record.sceneRoot)) {
				record.changer->sceneRoot = sceneRoot->root;
				break;
			}
		}
	}

	fileStream.close();
}

void TextLoader::Error(const char* message)
{
	MessageBox(NULL, message, "�籾��ȡʱ��������!", MB_ICONEXCLAMATION);
	//TODO ���ļ�
	exit(1);
}

void TextLoader::Error(const std::string & message)
{
	Error(message.c_str());
}

inline void TextLoader::AddNext(TextUnit * newUnit)
{
	if (unitPtrStack.top() == nullptr) {
		Error("��Ч����!\n\n��������:" + lineBuffer);
		return;
	}
	unitPtrStack.top()->next = newUnit;
	unitPtrStack.top() = unitPtrStack.top()->next;
}
