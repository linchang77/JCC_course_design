#pragma once

#ifndef SETTING_H
#define SETTING_H

#include "cocos2d.h"

class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//菜单回调
	void menuReturnCallback(cocos2d::Ref* pSender);
	void musicSwitchCallback(cocos2d::Ref* pSender);

	//实现create方法
	CREATE_FUNC(Setting);

	//菜单创建处理
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, float x, float y);

private:
	//Scene* self;																	//单例
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //坐标原点

	//设置项
	bool music = true;
};

#endif // !SETTING_H 
