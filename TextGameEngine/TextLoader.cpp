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
	std::ifstream fileStream;	//文件流
	fileStream.open("data.mts", std::ios::in);
	std::vector<recordSceneToChange> sceneChangeRecord;	//记录要转换场景的地方
	std::stack<TextUnitOptions*> optionStack;	//选项单元缓冲栈
	optionStack.push(nullptr);


	//开始循环
	while (!fileStream.eof()) {
		///获取数据
		std::getline(fileStream, lineBuffer);
		bool optionStatus = false;	//记录是否在选项编辑状态
		///进行操作
		//第一步:去掉开头的\t
		size_t begin = 0;
		for (;begin < lineBuffer.size() && lineBuffer.at(begin) == '\t'; begin++) {}

		//第二步,判断指令类型
		if (begin == lineBuffer.size()) {
			//是空行
			if (unitPtrStack.empty() || optionStack.top() != nullptr || unitPtrStack.top() == nullptr) {
				continue;
			}
			AddNext(new TextUnitEmpty());
		}
		else if (lineBuffer.at(begin) == '#') {
			//是注释
			continue;
		}
		else if (lineBuffer.at(begin) == '}') {
			//是选项内容的结束
			if (lineBuffer.substr(begin).size() != 1) {
				Error("}后面不能有东西!\n\n错误内容:" + lineBuffer);
				return;
			}
			optionStack.pop();
			unitPtrStack.pop();
			continue;
		}
		else if (lineBuffer.at(begin) == '[') {
			//是指令
			size_t endSign = lineBuffer.find(']', begin);

			if (endSign == std::string::npos) {
				Error("找不到对应的]\n\n错误内容:" + lineBuffer);
				return;
			}

			//获取指令内容
			std::string order = lineBuffer.substr(begin + 1, endSign - begin - 1);
			if (order.front() == '/') {
				if (order.size() == 2) {
					//定义选项内容
					size_t number = order.back() - '0';

					if (number < 0 || number>9) {
						Error("无效指令!\n\n错误内容:" + lineBuffer);
						return;
					}

					if (optionStack.top() == nullptr || optionStack.top()->options.size() <= number) {
						Error("没有对应的选项!\n\n错误内容:" + lineBuffer);
						return;
					}

					if (optionStack.top()->options.at(number).ptr != nullptr) {
						Error("选项已经被定义!\n\n错误内容:" + lineBuffer);
						return;
					}

					std::string orderMessage = lineBuffer.substr(endSign + 1);
					if (orderMessage.front() == '{') {
						if (orderMessage.size() != 1) {
							Error("{后面现在不支持加上别的东西(因为那样会比较难写),{后面的内容换一行吧!\n\n错误内容:" + lineBuffer);
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
					//创建新场景
					if (unitPtrStack.size() > 1) {
						Error("建立新场景的指令不能出现在这里!\n\n错误内容:" + lineBuffer);
						return;
					}

					std::string name = order.substr(1);

					for each (TextScene* sceneRoot in world.scenes)
					{
						int i = 0;
						if (sceneRoot->name._Equal(name)) {
							Error("不允许场景重名!\n\n错误内容:" + lineBuffer);
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
					Error("未指定场景!\n\n错误内容:" + lineBuffer);
					return;
				}

				if (order.size() == 1) {
					//创建选项
					int number = order.back() - '0';

					if (number < 0 || number>9) {
						Error("无效指令!\n\n错误内容:" + lineBuffer);
						return;
					}

					std::string orderMessage = lineBuffer.substr(endSign + 1);
					if (number == 0) {
						//创建新的选项单元
						optionStack.top() = new TextUnitOptions();
						AddNext(optionStack.top());
						optionStack.top()->options.push_back(TextUnitOptions::Option{ orderMessage ,nullptr });
					}
					else if (optionStack.top() == nullptr || number != optionStack.top()->options.size()) {
						Error("选项序号没有按照顺序!\n\n错误内容:" + lineBuffer);
						return;
					}
					else {
						optionStack.top()->options.push_back(TextUnitOptions::Option{ orderMessage ,nullptr });
					}

					optionStatus = true;
				}
				else if (order.find("to ") == 0) {
					//转换场景
					TextUnitSceneChange* changer = new TextUnitSceneChange();
					sceneChangeRecord.push_back(recordSceneToChange{ changer, order.substr(3) });
					AddNext(changer);
					unitPtrStack.top() = nullptr;
				}
				else {
					Error("无效指令!\n\n错误内容:" + lineBuffer);
					return;
				}
			}
		}
		else {
			//是文本
			if (unitPtrStack.empty()) {
				Error("文本内容未指定场景!\n\n错误内容:" + lineBuffer);
				return;
			}

			AddNext(new TextUnitString(lineBuffer.substr(begin)));
		}

		if (optionStack.top() != nullptr && !optionStatus) {
			//若结束编辑选项,则更新选项栈顶内容
			optionStack.top() = nullptr;
		}
	}

	//延迟处理场景转换信息
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
	MessageBox(NULL, message, "剧本读取时出现问题!", MB_ICONEXCLAMATION);
	//TODO 打开文件
	exit(1);
}

void TextLoader::Error(const std::string & message)
{
	Error(message.c_str());
}

inline void TextLoader::AddNext(TextUnit * newUnit)
{
	if (unitPtrStack.top() == nullptr) {
		Error("无效内容!\n\n错误内容:" + lineBuffer);
		return;
	}
	unitPtrStack.top()->next = newUnit;
	unitPtrStack.top() = unitPtrStack.top()->next;
}
