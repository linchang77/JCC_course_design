#pragma once

#ifndef SETTING_H
#define SETTING_H

#include "cocos2d.h"

#define NUM_PARAMETERS 1	//设置项个数

//设置项枚举
enum ParameterType { Music };

//设置项结构体
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

	//菜单回调
	void menuReturnCallback(cocos2d::Ref* pSender);
	void musicSwitchCallback(cocos2d::Ref* pSender);

	//创建单个设置项（输入按钮位置，锚点默认中心）
	cocos2d::MenuItemImage* setParameter(const ParameterType type, const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y);

	//实现create方法
	CREATE_FUNC(Setting);

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
};

//设置选项参数集
class SettingParameters
{
public:
	//该类是单例的
	static SettingParameters* getInstance();
	bool getValue(const ParameterType type);
	std::string getName(const ParameterType type);
	void setValue(const ParameterType type, bool value);

private:
	//设置项列表
	Parameter parameters[NUM_PARAMETERS] = {
		{ true, "music" } };
};

#endif // !SETTING_H 
