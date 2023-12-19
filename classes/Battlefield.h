#pragma once

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"
//模式选项
enum Mode { Practice, Battle };

//需用图层
class Store;
class Board;
class Preparation;

//通用战场类
class Battlefield : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//菜单回调
	void menuReturnCallback(cocos2d::Ref* pSender);
	void menuSetCallback(cocos2d::Ref* pSender);
	void menuStoreCallback(cocos2d::Ref* pSender);

	//实现create方法
	CREATE_FUNC(Battlefield);

	//菜单按钮创建处理
	cocos2d::MenuItemImage* createMenuItem(const std::string& normalImage, const std::string& selectedImage, const cocos2d::ccMenuCallback& callback, const float x, const float y, const float anchorX = 0.5f, const float anchorY = 0.5f);

private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize(); //屏幕尺寸
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();    //坐标原点
	cocos2d::Menu* store = nullptr;													//商店（与给定战场相绑定）
	cocos2d::Layer* preparation = nullptr;											//备战席（与给定战场相绑定）
};

//模式选择器，与具体的战斗场景相绑定
class ModeSelector
{
public:
	//模式选择器是单例的
	static ModeSelector* getInstance();
	bool setMode(const Mode mode, cocos2d::Scene* scene);
	Mode getMode(); 

private:
	Mode mode;
	cocos2d::Scene* scene;
};

//商店界面
class Store : public cocos2d::Menu
{
public:
	//随机显示英雄
	void randomDisplay();

	//实现create方法
	CREATE_FUNC(Store);

private:
	//英雄池
	cocos2d::Vector<Hero*> pool;
};

//棋盘
class Board : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	//实现create方法
	CREATE_FUNC(Board);

private:

};

//备战席
class Preparation : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	//实现create方法
	CREATE_FUNC(Preparation);

private:
	const std::string seat = "preparationSeat.png";	//单个席位图片
	const int size = 9;								//备战席尺寸
};

#endif // !BATTLEFIELD_H
