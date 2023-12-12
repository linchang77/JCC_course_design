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

<<<<<<< HEAD
	//菜单按钮创建处理
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//标签创建处理
	cocos2d::Label* createLabel(const std::string& text, const std::string& font, const float fontSize, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
=======
	//菜单创建处理
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, float x, float y);
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2

private:
	//Scene* self;																	//单例
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //坐标原点

	//设置项
	bool music = true;
<<<<<<< HEAD
	
=======
>>>>>>> 42ecac6567186336236054f09ece5dfd68a503d2
};

#endif // !SETTING_H 
