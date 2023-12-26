#pragma once

#ifndef SETTING_H
#define SETTING_H

#include "cocos2d.h"

#define NUM_PARAMETERS 1	//���������

//������ö��
enum ParameterType { Music };

//������ṹ��
struct Parameter
{
	bool value;
	std::string name;
};

class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//�˵��ص�
	void menuReturnCallback(cocos2d::Ref* pSender);
	void musicSwitchCallback(cocos2d::Ref* pSender);

	//����������������밴ťλ�ã�ê��Ĭ�����ģ�
	cocos2d::MenuItemImage* setParameter(const ParameterType type, const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y);

	//ʵ��create����
	CREATE_FUNC(Setting);

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
};

//����ѡ�������
class SettingParameters
{
public:
	//�����ǵ�����
	static SettingParameters* getInstance();
	bool getValue(const ParameterType type);
	std::string getName(const ParameterType type);
	void setValue(const ParameterType type, bool value);

private:
	//�������б�
	Parameter parameters[NUM_PARAMETERS] = {
		{ true, "music" } };
};

#endif // !SETTING_H 
