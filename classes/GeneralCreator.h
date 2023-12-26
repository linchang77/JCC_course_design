#pragma once

#ifndef GENERAL_CREATOR_H
#define GENERAL_CREATOR_H

#include "cocos2d.h"

//部分结点及其派生类的一键生成器
class GCreator
{
public:
	static GCreator* getInstance();						//获取单例

	//创建精灵
	cocos2d::Sprite* createSprite(const std::string& image, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//创建菜单项
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);
	
	//创建标签
	cocos2d::Label* createLabel(const std::string& text, const std::string& font, const float fontSize, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);	
	
	static void problemLoading(const std::string filename);	//输出错误信息

private:
	cocos2d::Size visibleSize;	//屏幕尺寸
	cocos2d::Vec2 origin;		//坐标原点
};

#endif // !GENERAL_CREATOR_H
